#include "ReadData.h"


// Đọc dữ liệu từ bảng music_info
vector<Music> ReadMusic::readData() const {
    vector<Music> items;
    DatabaseConnector dbConnector;

    if (!dbConnector.connect()) {
        return items;
    }

    SQLHDBC hDbc = dbConnector.getConnection();  // Lấy kết nối từ DatabaseConnector
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 3. Tạo và thực thi truy vấn SELECT
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
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
    dbConnector.disconnect();

    return items;
}

// Đọc dữ liệu từ bảng user_info
vector<shared_ptr<IUser>> ReadUser::readData() const {
    vector<shared_ptr<IUser>> users;
    DatabaseConnector dbConnector;

    if (!dbConnector.connect()) {
        return users;
    }

    SQLHDBC hDbc = dbConnector.getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 3. Tạo và thực thi truy vấn SELECT
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
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
    dbConnector.disconnect();

    return users;
}

// Đọc dữ liệu từ bảng orders và detail_order
vector<Order> ReadOrder::readData() const {
    vector<Order> orders;
    DatabaseConnector dbConnector;

    if (!dbConnector.connect()) {
        return orders;
    }

    SQLHDBC hDbc = dbConnector.getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 3. Lấy dữ liệu: mỗi dòng là 1 đơn hàng, gom theo OrderCode (dù không cần lưu nó)
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return orders;
    }

    string query = R"(
        SELECT Username, TotalPrice, NameSong, Artist, Genre, Price, Quantity
        FROM orders
        JOIN detail_order ON orders.OrderCode = detail_order.OrderCode
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

        SQLINTEGER prevOrderCode = -1, currentOrderCode;
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

            // Nếu là dòng đầu tiên hoặc đơn hàng mới (phân biệt bằng reset purchasedItems mỗi khi đổi Username + TotalPrice)
            if (!first && (Username != lastUsername || TotalPrice != currentTotalPrice)) {
                orders.emplace_back(Order(lastUsername, purchasedItems, currentTotalPrice));
                purchasedItems.clear();
            }

            first = false;
            lastUsername = Username;
            currentTotalPrice = TotalPrice;

            // Thêm sản phẩm vào danh sách
            purchasedItems.emplace_back(Music(NameSong, Artist, Genre, Price, Quantity));
        }

        // Thêm đơn hàng cuối cùng nếu có
        if (!purchasedItems.empty()) {
            orders.emplace_back(Order(lastUsername, purchasedItems, currentTotalPrice));
        }
    }

    // 4. Dọn dẹp tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();

    return orders;
}

// Đọc dữ liệu từ bảng vouchers
vector<shared_ptr<Discount>> ReadDiscount::readData() const {
    vector<shared_ptr<Discount>> vouchers;
    DatabaseConnector dbConnector;

    if (!dbConnector.connect()) {
        return vouchers;
    }

    SQLHDBC hDbc = dbConnector.getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // 3. Tạo và thực thi truy vấn SELECT
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
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

            shared_ptr<Discount> voucher = Discount::fromString(Voucher);
            vouchers.push_back(voucher);
        }
    }

    // 4. Dọn dẹp tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();

    return vouchers;
}
