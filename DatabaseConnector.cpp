#include "DatabaseConnector.h"

// handle errors that occur during database operations
void ODBCErrorHandler::showError(SQLHANDLE handle, SQLSMALLINT type) {
    SQLCHAR sqlState[6], message[256];
    SQLINTEGER nativeError;
    SQLSMALLINT msgLen;
    SQLRETURN ret = SQLGetDiagRec(type, handle, 1, sqlState, &nativeError, message, sizeof(message), &msgLen);
    
    if (SQL_SUCCEEDED(ret)) {
        std::cerr << "SQL Error: " << message << " (SQL State: " << sqlState << ")" << std::endl;
    } else {
        std::cerr << "Failed to retrieve error information." << std::endl;
    }
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
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    SQLRETURN ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    // Handle connection errors
    if (!SQL_SUCCEEDED(ret)) {
        showError();
        disconnect();
        return false;
    }

    // Update connection state and return success
    connected = true;
    return true;
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
void DatabaseConnector::showError() const {
    ODBCErrorHandler::showError(hDbc, SQL_HANDLE_DBC);
}
