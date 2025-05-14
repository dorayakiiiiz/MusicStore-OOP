#include "SQLUserRepository.h"

// sua cai nay


// #include <memory>

// SqlUserRepository::SqlUserRepository() {}

// SqlUserRepository::~SqlUserRepository() {}

// vector<User> SqlUserRepository::getAll() {
//     vector<User> users;
    
//     if (!dbConnector.connect()) {
//         return users;
//     }

//     SQLHSTMT hStmt = nullptr;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return users;
//     }

//     std::string query = "SELECT Username, Pass, UserRole FROM user_info";
//     SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);

//     if (SQL_SUCCEEDED(ret)) {
//         char usernameBuffer[100], passwordBuffer[100], roleBuffer[20];
//         SQLLEN usernameLen, passwordLen, roleLen;

//         SQLBindCol(hStmt, 1, SQL_C_CHAR, usernameBuffer, sizeof(usernameBuffer), &usernameLen);
//         SQLBindCol(hStmt, 2, SQL_C_CHAR, passwordBuffer, sizeof(passwordBuffer), &passwordLen);
//         SQLBindCol(hStmt, 3, SQL_C_CHAR, roleBuffer, sizeof(roleBuffer), &roleLen);

//         while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
//             std::string username(usernameBuffer);
//             std::string password(passwordBuffer);
//             std::string role(roleBuffer);
            
//             if (role == "Admin") {
//                 users.push_back(Admin(username, password));
//             } else {
//                 users.push_back(Customer(username, password));
//             }
//         }
//     }

//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return users;
// }


// bool SqlUserRepository::add(const User& user) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     std::string query = "INSERT INTO user_info (Username, Pass, UserRole) VALUES (?, ?, ?)";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         std::string username = user.getUsername();
//         std::string password = user.getPassword();
//         std::string role = (user.getRole() == Role::ADMIN) ? "Admin" : "Customer";
        
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, 
//                         (SQLCHAR*)username.c_str(), username.length(), NULL);
//         SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, password.length(), 0, 
//                         (SQLCHAR*)password.c_str(), password.length(), NULL);
//         SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, role.length(), 0, 
//                         (SQLCHAR*)role.c_str(), role.length(), NULL);
        
//         ret = SQLExecute(hStmt);
//         success = SQL_SUCCEEDED(ret);
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return success;
// }

// bool SqlUserRepository::deleteById(int id) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     std::string query = "DELETE FROM user_info WHERE Id = ?";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, NULL);
        
//         ret = SQLExecute(hStmt);
//         success = SQL_SUCCEEDED(ret);
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return success;
// }
