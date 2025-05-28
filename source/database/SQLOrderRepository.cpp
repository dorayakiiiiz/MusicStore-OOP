#include "SQLOrderRepository.h"
#include "DatabaseConnector.h"
#include "../models/Order.h"
#include "../models/Music.h"
#include <vector>

SqlOrderRepository::SqlOrderRepository() {}

SqlOrderRepository::~SqlOrderRepository() {}

vector<Order> SqlOrderRepository::getAll() {
    vector<Order> orders;

    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    if (!dbConnector->ensureConnected()) {
        return orders;
    }

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return orders;
    }

    string query = R"(
                    SELECT Username, TotalPrice, NameSong, Artist, Genre, Price, Quantity
                    FROM orders
                    JOIN detail_order ON orders.ID = detail_order.ID
                    ORDER BY orders.ID
                    )";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        char tempUsername[256], tempNameSong[256], tempArtist[256], tempGenre[100];
        string Username, NameSong, Artist, Genre;
        float Price, TotalPrice;
        int Quantity;

        string lastUsername = "";
        float currentTotalPrice = 0.0f;
        vector<Music> purchasedItems;

        bool first = true;

        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempUsername, sizeof(tempUsername), NULL);
            SQLGetData(hStmt, 2, SQL_C_FLOAT, &TotalPrice, 0, NULL);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempNameSong, sizeof(tempNameSong), NULL);
            SQLGetData(hStmt, 4, SQL_C_CHAR, tempArtist, sizeof(tempArtist), NULL);
            SQLGetData(hStmt, 5, SQL_C_CHAR, tempGenre, sizeof(tempGenre), NULL);
            SQLGetData(hStmt, 6, SQL_C_FLOAT, &Price, 0, NULL);
            SQLGetData(hStmt, 7, SQL_C_SLONG, &Quantity, 0, NULL);

            Username = tempUsername;
            NameSong = tempNameSong;
            Artist = tempArtist;
            Genre = tempGenre;

            if (!first && (Username != lastUsername || TotalPrice != currentTotalPrice)) {
                orders.emplace_back(Order(lastUsername, purchasedItems, currentTotalPrice));
                purchasedItems.clear();
            }

            first = false;
            lastUsername = Username;
            currentTotalPrice = TotalPrice;

            purchasedItems.emplace_back(Music(NameSong, Artist, Genre, Price, Quantity));
        }

        if (!purchasedItems.empty()) {
            orders.emplace_back(Order(lastUsername, purchasedItems, currentTotalPrice));
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return orders;
}

bool SqlOrderRepository::add(const Order& order) {
    bool success = false;
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    if (!dbConnector->ensureConnected()) {
        return false;
    }
    SQLHDBC hDbc = dbConnector->getConnection();

    // Turn off autocommit to use transaction
    SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);

    int newOrderId = 1;
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        string getMaxIdQuery = "SELECT ISNULL(MAX(ID), 0) + 1 FROM orders";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)getMaxIdQuery.c_str(), SQL_NTS);
        if (SQL_SUCCEEDED(ret) && SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_SLONG, &newOrderId, 0, NULL);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        hStmt = nullptr;
    }

    // Add to orders table
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        string insertOrderQuery = "INSERT INTO orders (ID, Username, TotalPrice) VALUES (?, ?, ?)";
        ret = SQLPrepare(hStmt, (SQLCHAR*)insertOrderQuery.c_str(), SQL_NTS);

        if (SQL_SUCCEEDED(ret)) {
            string username = order.getUsername();
            float total = order.getTotal();
            SQLLEN lenUsername = (SQLLEN)username.length();

            SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &newOrderId, 0, NULL);
            SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)username.c_str(), lenUsername, NULL);
            SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 0, 0, &total, 0, NULL);

            ret = SQLExecute(hStmt);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        hStmt = nullptr;
    }

    if (!SQL_SUCCEEDED(ret)) {
        SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK);
        return false;
    }

    // Add to table detail_order
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK);
        return false;
    }

    string detailQuery = "INSERT INTO detail_order (ID, NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?, ?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)detailQuery.c_str(), SQL_NTS);

    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK);
        return false;
    }

    const vector<Music>& items = order.getPurchasedItems();
    for (const auto& item : items) {
        string name = item.getName();
        string artist = item.getArtist();
        string genre = item.getGenre();
        float price = item.getPrice();
        int quantity = item.getQuantity();

        SQLLEN lenName = (SQLLEN)name.length();
        SQLLEN lenArtist = (SQLLEN)artist.length();
        SQLLEN lenGenre = (SQLLEN)genre.length();

        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &newOrderId, 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), lenName, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), lenArtist, NULL);
        SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)genre.c_str(), lenGenre, NULL);
        SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 0, 0, &price, 0, NULL);
        SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &quantity, 0, NULL);

        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS); // reset

        if (!SQL_SUCCEEDED(ret)) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK);
            return false;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_COMMIT);

    return true;
}

bool SqlOrderRepository::deleteById(int id) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) {
        return false;
    }
    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;
    bool success = false;

    // Turn off autocommit to use transaction
    SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);

    do {
        // Step 1: Delete detail_order
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
            break;
        }
        string deleteDetail = "DELETE FROM detail_order WHERE ID = ?";
        if (SQLPrepare(hStmt, (SQLCHAR*)deleteDetail.c_str(), SQL_NTS) != SQL_SUCCESS ||
            SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr) != SQL_SUCCESS ||
            !SQL_SUCCEEDED(SQLExecute(hStmt))) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Step 2: Delete orders
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
            break;
        }
        string deleteOrder = "DELETE FROM orders WHERE ID = ?";
        if (SQLPrepare(hStmt, (SQLCHAR*)deleteOrder.c_str(), SQL_NTS) != SQL_SUCCESS ||
            SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr) != SQL_SUCCESS ||
            !SQL_SUCCEEDED(SQLExecute(hStmt))) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Step 3: Get all remaining IDs
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
            break;
        }
        string selectQuery = "SELECT ID FROM orders ORDER BY ID ASC";
        if (SQLPrepare(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS) != SQL_SUCCESS ||
            SQLExecute(hStmt) != SQL_SUCCESS) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }

        vector<int> oldIds;
        int currentId;
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            if (SQLGetData(hStmt, 1, SQL_C_SLONG, &currentId, 0, nullptr) == SQL_SUCCESS) {
                oldIds.push_back(currentId);
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Step 4: Re-enter ID
        for (int i = 0; i < (int)oldIds.size(); ++i) {
            int oldId = oldIds[i];
            int newId = i + 1;
            if (oldId == newId) {
                continue;
            }
            int tmpId = -oldId;

            // Temporarily change ID detail_order to negative ID
            if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
                break;
            }
            string tmpUpdate = "UPDATE detail_order SET ID = ? WHERE ID = ?";
            if (SQLPrepare(hStmt, (SQLCHAR*)tmpUpdate.c_str(), SQL_NTS) != SQL_SUCCESS ||
                SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &tmpId, 0, nullptr) != SQL_SUCCESS ||
                SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &oldId, 0, nullptr) != SQL_SUCCESS ||
                !SQL_SUCCEEDED(SQLExecute(hStmt))) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

            // Change ID in orders
            if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
                break;
            }
            string updateOrder = "UPDATE orders SET ID = ? WHERE ID = ?";
            if (SQLPrepare(hStmt, (SQLCHAR*)updateOrder.c_str(), SQL_NTS) != SQL_SUCCESS ||
                SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr) != SQL_SUCCESS ||
                SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &oldId, 0, nullptr) != SQL_SUCCESS ||
                !SQL_SUCCEEDED(SQLExecute(hStmt))) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

            // Restore detail_order ID to new ID
            if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
                break;
            }
            string restoreDetail = "UPDATE detail_order SET ID = ? WHERE ID = ?";
            if (SQLPrepare(hStmt, (SQLCHAR*)restoreDetail.c_str(), SQL_NTS) != SQL_SUCCESS ||
                SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr) != SQL_SUCCESS ||
                SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &tmpId, 0, nullptr) != SQL_SUCCESS ||
                !SQL_SUCCEEDED(SQLExecute(hStmt))) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }

        success = true;

    } while (false);

    // Commit or rollback
    if (success) {
        SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_COMMIT);
    } else {
        SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK);
    }
    // Turn autocommit back on
    SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, 0);

    return success;
}

// do nothing
bool SqlOrderRepository::updateById(int id, const Order& order) { 
    return false; 
}

// do nothing
Order SqlOrderRepository::getById(int id) {
    Order order("", {}, 0.0f);
    return order;
}