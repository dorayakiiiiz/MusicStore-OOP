#include "ReadData.h"

using std::string;

vector<Music> ReadMusic::readData(const string& filename) const {
    vector<Music> items;
    SQLHENV hEnv = nullptr;
    SQLHDBC hDbc = nullptr;
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo môi trường
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return items;
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return items;
    }

    // 2. Kết nối CSDL
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return items;
    }

    // 3. Tạo và thực thi truy vấn SELECT
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return items;
    }

    string selectQuery = "SELECT NameSong, Artist, Genre, Price, Quantity FROM music_info";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        char tempNameSong[256], tempArtist[256], tempGenre[100];
        float price;
        int quantity;

        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempNameSong, sizeof(tempNameSong), NULL);
            SQLGetData(hStmt, 2, SQL_C_CHAR, tempArtist, sizeof(tempArtist), NULL);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempGenre, sizeof(tempGenre), NULL);
            SQLGetData(hStmt, 4, SQL_C_FLOAT, &price, 0, NULL);
            SQLGetData(hStmt, 5, SQL_C_SLONG, &quantity, 0, NULL);

            string nameSong = tempNameSong;
            string artist = tempArtist;
            string genre = tempGenre;

            items.emplace_back(nameSong, artist, genre, price, quantity);
        }
    }

    // 4. Dọn dẹp tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return items;
}


vector<shared_ptr<IUser>> ReadUser::readData(const string& filename) const {
    vector<shared_ptr<IUser>> users;
    SQLHENV hEnv = nullptr;
    SQLHDBC hDbc = nullptr;
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo môi trường
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return users;
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return users;
    }

    // 2. Kết nối CSDL
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return users;
    }

    // 3. Tạo và thực thi truy vấn SELECT
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return users;
    }

    string selectQuery = "SELECT Username, Pass, UserRole FROM user_info";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        char tempUsername[256], tempPass[256], tempRole[2];
        string username, password, role;

        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempUsername, sizeof(tempUsername), NULL);
            SQLGetData(hStmt, 2, SQL_C_CHAR, tempPass, sizeof(tempPass), NULL);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempRole, sizeof(tempRole), NULL);

            username = tempUsername;
            password = tempPass;
            role = tempRole;

            if (role == "C") {
                users.push_back(make_shared<Customer>(username, password));
            } else {
                users.push_back(make_shared<Admin>(username, password));
            }
        }
    }

    // 4. Dọn dẹp tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return users;
}


vector<Order> ReadOrder::readData(const string& filename) const {
    ifstream file(filename);
    vector<Order> orders;
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, totalPrice, items;
        getline(ss, username, '|');
        getline(ss, totalPrice, '|');
        getline(ss, items);

        vector<Music> purchasedItems;
        stringstream itemsStream(items);
        string itemSS;
        while (getline(itemsStream, itemSS, '|')) {
            stringstream itemsStream(itemSS);
            string name, artist, genre, price, quantity;
            getline(itemsStream, name, ';');
            getline(itemsStream, artist, ';');
            getline(itemsStream, genre, ';');
            getline(itemsStream, price, ';');
            getline(itemsStream, quantity, '|');

            Music item(name, artist, genre, stof(price), stoi(quantity));
            purchasedItems.emplace_back(item);
        }
        Order order(username, purchasedItems, stof(totalPrice));
        orders.push_back(order);
    }

    file.close();
    return orders;
}


vector<shared_ptr<IDiscount>> ReadDiscount::readData(const string& filename) const {
    vector<shared_ptr<IDiscount>> vouchers;

    SQLHENV hEnv = nullptr;
    SQLHDBC hDbc = nullptr;
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 1. Khởi tạo môi trường
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return vouchers;
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return vouchers;
    }

    // 2. Kết nối CSDL
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return vouchers;
    }

    // 3. Tạo và thực thi truy vấn SELECT
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return vouchers;
    }

    string selectQuery = "SELECT Vouchername FROM vouchers";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        char tempVoucher[256];
        string Voucher;

        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempVoucher, sizeof(tempVoucher), NULL);

            Voucher = tempVoucher;

            shared_ptr<IDiscount> voucher = IDiscount::toDiscount(Voucher);
            vouchers.push_back(voucher);
        }
    }

    // 4. Dọn dẹp tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return vouchers;
}