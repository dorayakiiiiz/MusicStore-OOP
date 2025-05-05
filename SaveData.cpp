#include "SaveData.h"
#include "DatabaseConnector.h"

// Implements the saveData method for Music objects
// Persists a collection of Music objects to the database
void SaveMusic::saveData(const vector<Music>& items) const {
    DatabaseConnector dbConnector; // Create a database connector instance
    SQLHSTMT hStmt = nullptr;      // SQL statement handle
    SQLRETURN ret;                 // Return value for SQL operations

    // Step 1: Connect to the database
    if (!dbConnector.connect()) return;

    // Step 2: Clear existing data from the music_info table
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM music_info";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);    // Clean up statement handle
    }

    // Step 3: Prepare insert statement for new data
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return;
    }

    // Define parameterized SQL query for inserting music data
    string insertQuery = "INSERT INTO music_info (NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        dbConnector.disconnect();
        return;
    }

    // Step 4: Insert each music item into the database
    for (const auto& item : items) {
        // Extract properties from the Music object
        string name = item.getName();
        string artist = item.getArtist();
        string genre = item.getGenre();
        float price = item.getPrice();
        int quantity = item.getQuantity();

        // Bind parameters to the prepared statement
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)genre.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, &price, 0, NULL);
        SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 0, 0, &quantity, 0, NULL);

        // Execute the SQL statement
        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS);    // Reset parameters for next iteration
    }

    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();
}

// Implements the saveData method for User objects
// Persists a collection of User objects to the database
void SaveUser::saveData(const vector<shared_ptr<IUser>>& users) const {
    DatabaseConnector dbConnector; // Create a database connector instance
    SQLHSTMT hStmt = nullptr;      // SQL statement handle
    SQLRETURN ret;                 // Return value for SQL operations

    // Step 1: Connect to the database
    if (!dbConnector.connect()) return;

    // Step 2: Clear existing data from the user_info table
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM user_info";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);    // Clean up statement handle
    }

    // Step 3: Prepare insert statement for new user data
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return;
    }

    // Define parameterized SQL query for inserting user data
    string insertQuery = "INSERT INTO user_info (Username, Pass, UserRole) VALUES (?, ?, ?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        dbConnector.disconnect();
        return;
    }

    // Step 4: Insert each user into the database
    for (const auto& user : users) {
        // Extract properties from the User object
        string username = user->getUsername();
        string pass = user->getPassword();
        // Convert role to single-character format (A for Admin, C for Customer)
        string role = (user->getRole() == "Admin") ? "A" : "C";

        // Bind parameters to the prepared statement
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)pass.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 1, 0, (SQLPOINTER)role.c_str(), 0, NULL);

        // Execute the SQL statement
        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS);    // Reset parameters for next iteration
    }

    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();
}

// Implements the saveData method for Order objects
// Persists a collection of Order objects to the database
void SaveOrder::saveData(const vector<Order>& orders) const {
    DatabaseConnector dbConnector; // Create a database connector instance
    SQLHSTMT hStmt = nullptr;      // SQL statement handle
    SQLRETURN ret;                 // Return value for SQL operations

    // Step 1: Connect to the database
    if (!dbConnector.connect()) return;

    // Step 2: Clear existing data from both order tables
    // We need to delete from detail_order first due to foreign key constraints
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        SQLExecDirect(hStmt, (SQLCHAR*)"DELETE FROM detail_order", SQL_NTS);
        SQLExecDirect(hStmt, (SQLCHAR*)"DELETE FROM orders", SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);    // Clean up statement handle
    }

    // Step 3: Save each order and its items
    for (size_t i = 0; i < orders.size(); ++i) {
        const auto& order = orders[i];
        // Generate a unique order code from the index
        int orderCode = i + 1;

        // Insert the main order record
        if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) continue;

        string insertOrder = "INSERT INTO orders (OrderCode, Username, TotalPrice) VALUES (?, ?, ?)";
        ret = SQLPrepare(hStmt, (SQLCHAR*)insertOrder.c_str(), SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            continue;
        }

        // Extract order properties
        string username = order.getUsername();
        float total = order.getTotal();
        
        // Bind parameters for the order record
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &orderCode, 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 0, 0, &total, 0, NULL);
        
        // Execute the order insert statement
        if (!SQL_SUCCEEDED(SQLExecute(hStmt))) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            continue;
        }

        // Insert each item in the order into the detail_order table
        const auto& items = order.getPurchasedItems();
        for (const auto& item : items) {
            if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) continue;

            // Prepare the insert statement for order details
            string insertDetail = "INSERT INTO detail_order (OrderCode, NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?, ?)";
            ret = SQLPrepare(hStmt, (SQLCHAR*)insertDetail.c_str(), SQL_NTS);
            if (!SQL_SUCCEEDED(ret)) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                continue;
            }

            // Extract item properties
            string name = item.getName();
            string artist = item.getArtist();
            string genre = item.getGenre();
            float price = item.getPrice();
            int quantity = item.getQuantity();

            // Bind parameters for the order detail record
            SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &orderCode, 0, NULL);
            SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, NULL);
            SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, NULL);
            SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)genre.c_str(), 0, NULL);
            SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 0, 0, &price, 0, NULL);
            SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &quantity, 0, NULL);

            // Execute the detail insert statement
            SQLExecute(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
    }

    // Step 4: Clean up resources
    dbConnector.disconnect();
}

// Implements the saveData method for Discount objects
// Persists a collection of Discount objects to the database
void SaveDiscount::saveData(const vector<shared_ptr<Discount>>& vouchers) const {
    DatabaseConnector dbConnector; // Create a database connector instance
    SQLHSTMT hStmt = nullptr;      // SQL statement handle
    SQLRETURN ret;                 // Return value for SQL operations

    // Step 1: Connect to the database
    if (!dbConnector.connect()) return;

    // Step 2: Clear existing data from the vouchers table
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) == SQL_SUCCESS) {
        string deleteQuery = "DELETE FROM vouchers";
        ret = SQLExecDirect(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);    // Clean up statement handle
    }

    // Step 3: Prepare insert statement for voucher data
    if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
        dbConnector.disconnect();
        return;
    }

    // Define parameterized SQL query for inserting voucher data
    string insertQuery = "INSERT INTO vouchers (Vouchername) VALUES (?)";
    ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        dbConnector.disconnect();
        return;
    }

    // Step 4: Insert each voucher into the database
    // Vouchers are serialized into a string representation using the toString method
    for (const auto& voucher : vouchers) {
        // Convert the Discount object to its string representation
        string Voucher = voucher->toString();

        // Bind the voucher string parameter
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)Voucher.c_str(), 0, NULL);
        
        // Execute the SQL statement
        ret = SQLExecute(hStmt);
        SQLFreeStmt(hStmt, SQL_RESET_PARAMS);    // Reset parameters for next iteration
    }

    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    dbConnector.disconnect();
}
