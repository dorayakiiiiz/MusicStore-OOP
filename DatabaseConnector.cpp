#include "DatabaseConnector.h"

DatabaseConnector::DatabaseConnector() : hEnv(nullptr), hDbc(nullptr), connected(false) {}

DatabaseConnector::~DatabaseConnector() {
    disconnect();
}

bool DatabaseConnector::connect() {
    // 1. Khởi tạo môi trường
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) return false;
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return false;
    }

    // 2. Kết nối CSDL
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=music_store;Trusted_Connection=yes;";
    SQLRETURN ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    if (!SQL_SUCCEEDED(ret)) {
        showError();
        disconnect();
        return false;
    }

    connected = true;
    return true;
}

SQLHDBC DatabaseConnector::getConnection() const {
    return hDbc;
}

bool DatabaseConnector::isConnected() const {
    return connected;
}

void DatabaseConnector::disconnect() {
    if (hDbc) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        hDbc = nullptr;
    }
    if (hEnv) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        hEnv = nullptr;
    }
    connected = false;
}

void DatabaseConnector::showError() const {
    ODBCErrorHandler::showError(hDbc, SQL_HANDLE_DBC);
}
