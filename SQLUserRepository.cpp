#include "SQLUserRepository.h"
#include <memory>

using std::make_shared, std::shared_ptr;

SqlUserRepository::SqlUserRepository() {}

SqlUserRepository::~SqlUserRepository() {}

vector<shared_ptr<User>> SqlUserRepository::getAll() {
    vector<shared_ptr<User>> users;     // Container for user pointers

    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();     // Database connection object
    // Step 1: Connect to the database
    if (!dbConnector->ensureConnected()) {
        std::cerr << "Failed to connect to database" << std::endl;
        return users;  // Return empty vector if connection fails
    }

    SQLHDBC hDbc = dbConnector->getConnection();  // Get database connection handle
    SQLHSTMT hStmt = nullptr;                    // SQL statement handle
    SQLRETURN ret;                               // SQL operation return value

    // Step 2: Allocate a statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        std::cerr << "Failed to allocate statement handle" << std::endl;
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

    return users;  // Return the populated vector
}

bool SqlUserRepository::add(const shared_ptr<User>& user) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) return false;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    std::string username = user->getUsername();
    std::string password = user->getPassword();
    std::string role = (user->getRole() == Role::ADMIN) ? "A" : "C";

    // Step 1: Check duplicates
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return false;
    }

    std::string checkQuery = "SELECT COUNT(*) FROM user_info WHERE Username = ?";
    ret = SQLPrepare(hStmt, (SQLCHAR*)checkQuery.c_str(), SQL_NTS);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)username.c_str(), 0, nullptr);

    int duplicate = 0;
    if (SQLExecute(hStmt) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_SLONG, &duplicate, 0, nullptr);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (duplicate > 0) {
        return false;
    }

    // Step 2: Get next ID
    int newId = 1;
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        std::string idQuery = "SELECT ISNULL(MAX(ID), 0) + 1 FROM user_info";
        if (SQLExecDirect(hStmt, (SQLCHAR*)idQuery.c_str(), SQL_NTS) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_SLONG, &newId, 0, nullptr);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // Step 3: Insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return false;
    }

    std::string insertQuery = "INSERT INTO user_info (ID, Username, Pass, UserRole) VALUES (?, ?, ?, ?)";
    SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
    
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)username.c_str(), 0, nullptr);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)password.c_str(), 0, nullptr);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 1, 0, (SQLPOINTER)role.c_str(), 0, nullptr);

    bool success = SQL_SUCCEEDED(SQLExecute(hStmt));
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return success;
}

bool SqlUserRepository::deleteById(int id) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) return false;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;

    // Step 1: Delete record
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return false;
    }

    std::string deleteQuery = "DELETE FROM user_info WHERE ID = ?";
    SQLPrepare(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
    bool success = SQL_SUCCEEDED(SQLExecute(hStmt));
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // Step 2: Shift IDs
    if (success && SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        std::string selectQuery = "SELECT ID FROM user_info WHERE ID > ? ORDER BY ID ASC";
        SQLPrepare(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);

        if (SQLExecute(hStmt) == SQL_SUCCESS) {
            int currentId;
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_SLONG, &currentId, 0, nullptr);
                int newId = currentId - 1;

                SQLHSTMT hUpdateStmt = nullptr;
                if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hUpdateStmt) == SQL_SUCCESS) {
                    std::string updateQuery = "UPDATE user_info SET ID = ? WHERE ID = ?";
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

    return success;
}


// these methods are not implemented yet
shared_ptr<User> SqlUserRepository::getById(int id) { return nullptr; }
bool SqlUserRepository::updateById(int id, const shared_ptr<User>& user) { return false; }
