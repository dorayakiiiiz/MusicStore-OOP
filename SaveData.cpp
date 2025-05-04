#include "SaveData.h"


void SaveMusic::saveData(const string& filename, const vector<Music>& items) const {
    SQLHENV hEnv = nullptr;
    SQLHDBC hDbc = nullptr;
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo môi trường
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) 
        return;

    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 2. Kết nối
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 3. Xóa dữ liệu cũ
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM music_info";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // 4. Chuẩn bị insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    string insertQuery = "INSERT INTO music_info (NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 5. Ghi từng dòng vào CSDL
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

    // 6. Dọn dẹp
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv); 
}


void SaveUser::saveData(const string& filename, const vector<shared_ptr<IUser>>& users) const {
    SQLHENV hEnv = nullptr;
    SQLHDBC hDbc = nullptr;
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo môi trường
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return;
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 2. Kết nối
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 3. Xóa dữ liệu cũ
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM user_info";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // 4. Chuẩn bị insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    string insertQuery = "INSERT INTO user_info (Username, Pass, UserRole) VALUES (?, ?, ?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 5. Ghi từng dòng user vào CSDL
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

    // 6. Dọn dẹp
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv); 
}


void SaveOrder::saveData(const string& filename, const vector<Order>& orders) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    for (const auto& order : orders) {
        file << order.getUsername() << "|"
             << order.getTotal() << "|";
        const auto& items = order.getPurchasedItems();
        for (int i = 0; i < items.size(); ++i) {
            file << items[i].getName() << ";"
                 << items[i].getArtist() << ";"
                 << items[i].getGenre() << ";"
                 << items[i].getPrice() << ";"
                 << items[i].getQuantity() << "|";
        }
        file << "\n";
    }

    file.close();
}

void SaveDiscount::saveData(const string& filename, const vector<shared_ptr<IDiscount>>& vouchers) const {
    SQLHENV hEnv = nullptr;
    SQLHDBC hDbc = nullptr;
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo môi trường
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return;
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 2. Kết nối
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 3. Xóa dữ liệu cũ
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM vouchers";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // 4. Chuẩn bị insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    string insertQuery = "INSERT INTO vouchers (Vouchername) VALUES (?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return;
    }

    // 5. Ghi từng dòng user vào CSDL
    for (const auto& voucher : vouchers) {
        string Voucher = voucher->toString();

        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)Voucher.c_str(), 0, NULL);

        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS);
    }

    // 6. Dọn dẹp
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv); 
}