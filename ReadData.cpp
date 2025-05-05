/**
 * @file ReadData.cpp
 * @brief Implementation file for data reading classes
 * 
 * @details Contains implementations for loading different types of data
 *          (music, users, orders, discounts) from persistent storage
 */

#include "ReadData.h"

// Implements the readData method for Music class
// Reads all music records from the database and returns as a vector of Music objects
vector<Music> ReadMusic::readData() const {
    vector<Music> items;                 // Container for the music items
    DatabaseConnector dbConnector;       // Database connection manager

    // Step 1: Connect to the database
    if (!dbConnector.connect()) {
        return items;  // Return empty vector if connection fails
    }

    SQLHDBC hDbc = dbConnector.getConnection();  // Get database connection handle
    SQLHSTMT hStmt = nullptr;                    // SQL statement handle
    SQLRETURN ret;                               // SQL operation return value

    // Step 2: Allocate a statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return items;  // Return empty vector if handle allocation fails
    }

    // Step 3: Execute query to get all music records
    string selectQuery = "SELECT NameSong, Artist, Genre, Price, Quantity FROM music_info";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);

    // Step 4: Process query results
    if (SQL_SUCCEEDED(ret)) {
        // Temporary variables to store column data
        char tempNameSong[256], tempArtist[256], tempGenre[100];
        float price;
        int quantity;

        // Fetch each row from the result set
        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            // Get data from each column
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempNameSong, sizeof(tempNameSong), NULL);
            SQLGetData(hStmt, 2, SQL_C_CHAR, tempArtist, sizeof(tempArtist), NULL);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempGenre, sizeof(tempGenre), NULL);
            SQLGetData(hStmt, 4, SQL_C_FLOAT, &price, 0, NULL);
            SQLGetData(hStmt, 5, SQL_C_SLONG, &quantity, 0, NULL);

            // Convert char arrays to C++ strings
            string nameSong = tempNameSong;
            string artist = tempArtist;
            string genre = tempGenre;

            // Create a new Music object and add it to the result vector
            items.emplace_back(nameSong, artist, genre, price, quantity);
        }
    }

    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();

    return items;  // Return the populated vector
}

// Implements the readData method for User class
// Reads all user records from the database and returns as a vector of IUser pointers
vector<shared_ptr<IUser>> ReadUser::readData() const {
    vector<shared_ptr<IUser>> users;     // Container for user pointers
    DatabaseConnector dbConnector;       // Database connection manager

    // Step 1: Connect to the database
    if (!dbConnector.connect()) {
        return users;  // Return empty vector if connection fails
    }

    SQLHDBC hDbc = dbConnector.getConnection();  // Get database connection handle
    SQLHSTMT hStmt = nullptr;                    // SQL statement handle
    SQLRETURN ret;                               // SQL operation return value

    // Step 2: Allocate a statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return users;  // Return empty vector if handle allocation fails
    }

    // Step 3: Execute query to get all user records
    string selectQuery = "SELECT Username, Pass, UserRole FROM user_info";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);

    // Step 4: Process query results
    if (SQL_SUCCEEDED(ret)) {
        // Temporary variables to store column data
        char tempUsername[256], tempPass[256], tempRole[2];
        string username, password, role;

        // Fetch each row from the result set
        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            // Get data from each column
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempUsername, sizeof(tempUsername), NULL);
            SQLGetData(hStmt, 2, SQL_C_CHAR, tempPass, sizeof(tempPass), NULL);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempRole, sizeof(tempRole), NULL);

            // Convert char arrays to C++ strings
            username = tempUsername;
            password = tempPass;
            role = tempRole;

            // Create appropriate user type based on role (C = Customer, otherwise Admin)
            if (role == "C") {
                users.push_back(make_shared<Customer>(username, password));
            } else {
                users.push_back(make_shared<Admin>(username, password));
            }
        }
    }

    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();

    return users;  // Return the populated vector
}

// Implements the readData method for Order class
// Reads all order records from the database and returns as a vector of Order objects
vector<Order> ReadOrder::readData() const {
    vector<Order> orders;                // Container for orders
    DatabaseConnector dbConnector;       // Database connection manager

    // Step 1: Connect to the database
    if (!dbConnector.connect()) {
        return orders;  // Return empty vector if connection fails
    }

    SQLHDBC hDbc = dbConnector.getConnection();  // Get database connection handle
    SQLHSTMT hStmt = nullptr;                    // SQL statement handle
    SQLRETURN ret;                               // SQL operation return value

    // Step 2: Allocate a statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return orders;  // Return empty vector if handle allocation fails
    }

    // Step 3: Execute query to get combined order and order detail records
    // This join query gets all order details along with order header information
    string query = R"(
        SELECT Username, TotalPrice, NameSong, Artist, Genre, Price, Quantity
        FROM orders
        JOIN detail_order ON orders.OrderCode = detail_order.OrderCode
    )";
    ret = SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);

    // Step 4: Process query results
    if (SQL_SUCCEEDED(ret)) {
        // Temporary variables to store column data
        char tempUsername[256], tempNameSong[256], tempArtist[256], tempGenre[100];
        string Username, NameSong, Artist, Genre;
        float Price, TotalPrice;
        int Quantity;

        // Variables to track the current order being built
        string lastUsername = "";
        float currentTotalPrice = 0.0f;
        vector<Music> purchasedItems;

        SQLINTEGER prevOrderCode = -1, currentOrderCode;
        bool first = true;

        // Fetch each row from the result set
        while ((ret = SQLFetch(hStmt)) == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            // Get data from each column
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempUsername, sizeof(tempUsername), NULL);
            SQLGetData(hStmt, 2, SQL_C_FLOAT, &TotalPrice, 0, NULL);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempNameSong, sizeof(tempNameSong), NULL);
            SQLGetData(hStmt, 4, SQL_C_CHAR, tempArtist, sizeof(tempArtist), NULL);
            SQLGetData(hStmt, 5, SQL_C_CHAR, tempGenre, sizeof(tempGenre), NULL);
            SQLGetData(hStmt, 6, SQL_C_FLOAT, &Price, 0, NULL);
            SQLGetData(hStmt, 7, SQL_C_SLONG, &Quantity, 0, NULL);

            // Convert char arrays to C++ strings
            Username = tempUsername;
            NameSong = tempNameSong;
            Artist = tempArtist;
            Genre = tempGenre;

            // If this is a new order (different username or total price), save the previous one
            // and start collecting items for the new order
            if (!first && (Username != lastUsername || TotalPrice != currentTotalPrice)) {
                orders.emplace_back(Order(lastUsername, purchasedItems, currentTotalPrice));
                purchasedItems.clear();
            }

            first = false;
            lastUsername = Username;
            currentTotalPrice = TotalPrice;

            // Add this item to the current order's purchased items
            purchasedItems.emplace_back(Music(NameSong, Artist, Genre, Price, Quantity));
        }

        // Add the last order if there are any items
        if (!purchasedItems.empty()) {
            orders.emplace_back(Order(lastUsername, purchasedItems, currentTotalPrice));
        }
    }

    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();

    return orders;  // Return the populated vector
}

// Implements the readData method for Discount class
// Reads all voucher records from the database and returns as a vector of Discount pointers
vector<shared_ptr<Discount>> ReadDiscount::readData() const {
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
