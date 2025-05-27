/**
 * @file DatabaseConnector.cpp
 * @brief Implementation file for the DatabaseConnector class
 * 
 * @details Contains implementations for database connectivity functionality,
 *          managing connections to data storage
 */

#include "DatabaseConnector.h"

// Initialize static members
DatabaseConnector* DatabaseConnector::instance = nullptr;


// handle errors that occur during database operations
// void ODBCErrorHandler::showError(SQLHANDLE handle, SQLSMALLINT type) {
//     SQLCHAR sqlState[6], message[256];
//     SQLINTEGER nativeError;
//     SQLSMALLINT msgLen;
//     SQLRETURN ret = SQLGetDiagRec(type, handle, 1, sqlState, &nativeError, message, sizeof(message), &msgLen);
    
//     if (SQL_SUCCEEDED(ret)) {
//         std::cerr << "SQL Error: " << message << " (SQL State: " << sqlState << ")" << std::endl;
//     } else {
//         std::cerr << "Failed to retrieve error information." << std::endl;
//     }
// }

// Get singleton instance 
DatabaseConnector* DatabaseConnector::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseConnector();
        instance->connect();  
    }
    return instance;
}

// Initialize class members to default values
DatabaseConnector::DatabaseConnector() : hEnv(nullptr), hDbc(nullptr), connected(false) {}

// Ensure proper cleanup when object is destroyed
DatabaseConnector::~DatabaseConnector() {
    disconnect();
}

// Establish a connection to the SQL Server database
bool DatabaseConnector::connect() {
    // Step 1: Initialize the ODBC environment
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return false;
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return false;
    }

    // Step 2: Connect to the database using connection string
    SQLCHAR connStr[] = 
    "Driver={ODBC Driver 17 for SQL Server};"
    "Server=tcp:musicstoredb.database.windows.net,1433;"
    "Database=music_store;"
    "Uid=adminuser;"
    "Pwd=23120197_23120209#OOP_CTT3;"
    "Encrypt=yes;"
    "TrustServerCertificate=no;"
    "Connection Timeout=30;";

    SQLRETURN ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    // Handle connection errors
    if (!SQL_SUCCEEDED(ret)) {
        // showError();
        disconnect();
        return false;
    }

    // Update connection state and return success
    connected = true;
    return true;
}

// Ensure connection is active, reconnect if needed
bool DatabaseConnector::ensureConnected() {
    if (!connected) {
        return connect();
    }
    
    // Test if connection is still alive
    if (!testConnection()) {
        // std::cout << "Database connection lost. Reconnecting..." << std::endl;
        disconnect();
        return connect();
    }
    
    return true;
}

// Test if connection is still active
bool DatabaseConnector::testConnection() const {
    if (!connected) return false;
    
    SQLHSTMT hStmt = nullptr;
    bool isValid = false;
    
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        // Simple query to test connection
        SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)"SELECT 1", SQL_NTS);
        isValid = SQL_SUCCEEDED(ret);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }
    
    return isValid;
}

// Retrieve the current database connection handle
SQLHDBC DatabaseConnector::getConnection() const {
    return hDbc;
}

// Check if there is an active database connection
bool DatabaseConnector::isConnected() const {
    return connected;
}

// Close the database connection and free associated resources
void DatabaseConnector::disconnect() {
    if (hDbc) {
        SQLDisconnect(hDbc);                   // Disconnect from database
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);   // Free connection handle
        hDbc = nullptr;
    }
    if (hEnv) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);   // Free environment handle
        hEnv = nullptr;
    }
    connected = false;  // Update connection state
}

// Display any ODBC errors that occurred during a connection operation
// void DatabaseConnector::showError() const {
//     ODBCErrorHandler::showError(hDbc, SQL_HANDLE_DBC);
// }

// Static cleanup method to call at program end
void DatabaseConnector::cleanup() {
    if (instance) {
        instance->disconnect();
        delete instance;
        instance = nullptr;
    }
}
