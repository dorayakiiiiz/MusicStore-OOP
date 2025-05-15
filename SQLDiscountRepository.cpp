#include "SQLDiscountRepository.h"
#include <memory>

using std::make_shared, std::make_unique;

SqlDiscountRepository::SqlDiscountRepository() {}

SqlDiscountRepository::~SqlDiscountRepository() {}

vector<shared_ptr<Discount>> SqlDiscountRepository::getAll() {
    vector<shared_ptr<Discount>> vouchers;  // Container for discount vouchers
    DatabaseConnector dbConnector;          // Database connection manager

    // Step 1: Connect to the database
    if (!dbConnector.connect()) {
        return vouchers;  // Return empty vector if connection fails
    }

    SQLHDBC hDbc = dbConnector.getConnection();  // Get database connection handle
    SQLHSTMT hStmt = nullptr;                    // SQL statement handle
    SQLRETURN ret;                               // SQL operation return value

    // Step 2: Allocate a statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return vouchers;  // Return empty vector if handle allocation fails
    }

    // Step 3: Execute query to get all voucher records
    string selectQuery = "SELECT Vouchername FROM vouchers";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);

    // Step 4: Process query results
    if (SQL_SUCCEEDED(ret)) {
        // Temporary variable to store voucher string
        char tempVoucher[256];
        string Voucher;

        // Fetch each row from the result set
        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempVoucher, sizeof(tempVoucher), NULL);

            Voucher = tempVoucher;

            // Deserialize the voucher string back to a Discount object
            shared_ptr<Discount> voucher = Discount::fromString(Voucher);
            vouchers.push_back(voucher);
        }
    }

    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();

    return vouchers;  // Return the populated vector
}

bool SqlDiscountRepository::add(const Discount& discount) {
    DatabaseConnector dbConnector;
    if (!dbConnector.connect()) return false;

    SQLHDBC hDbc = dbConnector.getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    std::string voucherString = discount.toString();
    
    // Step 1: Check duplicates
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return false;
    }

    std::string checkQuery = "SELECT COUNT(*) FROM vouchers WHERE Vouchername = ?";
    ret = SQLPrepare(hStmt, (SQLCHAR*)checkQuery.c_str(), SQL_NTS);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)voucherString.c_str(), 0, nullptr);

    int duplicate = 0;
    if (SQLExecute(hStmt) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_SLONG, &duplicate, 0, nullptr);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (duplicate > 0) {
        dbConnector.disconnect();
        return false;
    }

    // Step 2: Get next ID
    int newId = 1;
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        std::string idQuery = "SELECT ISNULL(MAX(ID), 0) + 1 FROM vouchers";
        if (SQLExecDirect(hStmt, (SQLCHAR*)idQuery.c_str(), SQL_NTS) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_SLONG, &newId, 0, nullptr);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // Step 3: Insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return false;
    }

    std::string insertQuery = "INSERT INTO vouchers (ID, Vouchername) VALUES (?, ?)";
    SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)voucherString.c_str(), 0, nullptr);

    bool success = SQL_SUCCEEDED(SQLExecute(hStmt));
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();
    return success;
}

bool SqlDiscountRepository::deleteById(int id) {
        DatabaseConnector dbConnector;
    if (!dbConnector.connect()) return false;

    SQLHDBC hDbc = dbConnector.getConnection();
    SQLHSTMT hStmt = nullptr;

    // Step 1: Delete record
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return false;
    }

    std::string deleteQuery = "DELETE FROM vouchers WHERE ID = ?";
    SQLPrepare(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
    bool success = SQL_SUCCEEDED(SQLExecute(hStmt));
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // Step 2: Shift IDs
    if (success && SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        std::string selectQuery = "SELECT ID FROM vouchers WHERE ID > ? ORDER BY ID ASC";
        SQLPrepare(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);

        if (SQLExecute(hStmt) == SQL_SUCCESS) {
            int currentId;
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_SLONG, &currentId, 0, nullptr);
                int newId = currentId - 1;

                SQLHSTMT hUpdateStmt = nullptr;
                if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hUpdateStmt) == SQL_SUCCESS) {
                    std::string updateQuery = "UPDATE vouchers SET ID = ? WHERE ID = ?";
                    SQLPrepare(hUpdateStmt, (SQLCHAR*)updateQuery.c_str(), SQL_NTS);
                    SQLBindParameter(hUpdateStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr);
                    SQLBindParameter(hUpdateStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &currentId, 0, nullptr);
                    SQLExecute(hUpdateStmt);
                    SQLFreeHandle(SQL_HANDLE_STMT, hUpdateStmt);
                }
            }
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    dbConnector.disconnect();
    return success;
}

