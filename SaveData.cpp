#include "SaveData.h"
#include "DatabaseConnector.h"

// Saves music data to a file
void SaveMusic::saveData(const vector<Music>& items) const {
    DatabaseConnector dbConnector; // Sử dụng DatabaseConnector
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Kết nối và khởi tạo môi trường từ DatabaseConnector
    if (!dbConnector.connect()) return;

    // 2. Xóa dữ liệu cũ
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM music_info";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // 3. Chuẩn bị insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return;
    }

    string insertQuery = "INSERT INTO music_info (NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        dbConnector.disconnect();
        return;
    }

    // 4. Ghi từng dòng vào CSDL
    for (const auto& item : items) {
        string name = item.getName();
        string artist = item.getArtist();
        string genre = item.getGenre();
        float price = item.getPrice();
        int quantity = item.getQuantity();

        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)genre.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, &price, 0, NULL);
        SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 0, 0, &quantity, 0, NULL);

        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS);
    }

    // 5. Dọn dẹp
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();
}

// Saves user data to a file
void SaveUser::saveData(const vector<shared_ptr<IUser>>& users) const {
    DatabaseConnector dbConnector; // Sử dụng DatabaseConnector
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Kết nối và khởi tạo môi trường từ DatabaseConnector
    if (!dbConnector.connect()) return;

    // 2. Xóa dữ liệu cũ
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM user_info";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // 3. Chuẩn bị insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return;
    }

    string insertQuery = "INSERT INTO user_info (Username, Pass, UserRole) VALUES (?, ?, ?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        dbConnector.disconnect();
        return;
    }

    // 4. Ghi từng dòng user vào CSDL
    for (const auto& user : users) {
        string username = user->getUsername();
        string pass = user->getPassword();
        string role = (user->getRole() == "Admin") ? "A" : "C";

        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)pass.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 1, 0, (SQLPOINTER)role.c_str(), 0, NULL);

        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS);
    }

    // 5. Dọn dẹp
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();
}

// Saves order data to a file
void SaveOrder::saveData(const vector<Order>& orders) const {
    DatabaseConnector dbConnector; // Sử dụng DatabaseConnector
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo và kết nối
    if (!dbConnector.connect()) return;

    // 2. Xóa dữ liệu cũ
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        SQLExecDirect(hStmt, (SQLCHAR*)"DELETE FROM detail_order", SQL_NTS);
        SQLExecDirect(hStmt, (SQLCHAR*)"DELETE FROM orders", SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // 3. Lưu đơn hàng
    for (size_t i = 0; i < orders.size(); ++i) {
        const auto& order = orders[i];
        int orderCode = i + 1;  // OrderCode là index + 1

        // Insert orders
        if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) continue;

        string insertOrder = "INSERT INTO orders (OrderCode, Username, TotalPrice) VALUES (?, ?, ?)";
        ret = SQLPrepare(hStmt, (SQLCHAR*)insertOrder.c_str(), SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            continue;
        }

        string username = order.getUsername();
        float total = order.getTotal();
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &orderCode, 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 0, 0, &total, 0, NULL);
        if (!SQL_SUCCEEDED(SQLExecute(hStmt))) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            continue;
        }

        // Insert detail_order
        const auto& items = order.getPurchasedItems();
        for (const auto& item : items) {
            if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) continue;

            string insertDetail = "INSERT INTO detail_order (OrderCode, NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?, ?)";
            ret = SQLPrepare(hStmt, (SQLCHAR*)insertDetail.c_str(), SQL_NTS);
            if (!SQL_SUCCEEDED(ret)) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                continue;
            }

            string name = item.getName();
            string artist = item.getArtist();
            string genre = item.getGenre();
            float price = item.getPrice();
            int quantity = item.getQuantity();

            SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &orderCode, 0, NULL);
            SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, NULL);
            SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, NULL);
            SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)genre.c_str(), 0, NULL);
            SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 0, 0, &price, 0, NULL);
            SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &quantity, 0, NULL);

            SQLExecute(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
    }

    // 4. Dọn dẹp
    dbConnector.disconnect();
}

void SaveDiscount::saveData(const vector<shared_ptr<Discount>>& vouchers) const {
    DatabaseConnector dbConnector; // Sử dụng DatabaseConnector
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo và kết nối
    if (!dbConnector.connect()) return;

    // 2. Xóa dữ liệu cũ
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM vouchers";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // 3. Chuẩn bị insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return;
    }

    string insertQuery = "INSERT INTO vouchers (Vouchername) VALUES (?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        dbConnector.disconnect();
        return;
    }

    // 4. Ghi từng voucher vào CSDL
    for (const auto& voucher : vouchers) {
        string Voucher = voucher->toString();

        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)Voucher.c_str(), 0, NULL);
        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS);
    }

    // 5. Dọn dẹp
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();
}
