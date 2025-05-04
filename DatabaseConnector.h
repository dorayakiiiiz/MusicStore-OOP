#ifndef _DATABASE_CONNECTOR_H_
#define _DATABASE_CONNECTOR_H_
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <iostream>
#include <string>
#include <vector>

using std::string;

class ODBCErrorHandler {
    public:
        static void showError(SQLHANDLE handle, SQLSMALLINT type) {
            SQLCHAR sqlState[1024];
            SQLCHAR message[1024];
            if (SQLGetDiagRec(type, handle, 1, sqlState, NULL, message, 1024, NULL) == SQL_SUCCESS) {
                std::cerr << "ODBC Error: " << message << " (SQLState: " << sqlState << ")\n";
            }
        }
};
    
class DatabaseConnector {
private:
    SQLHENV hEnv;
    SQLHDBC hDbc;
    bool connected;

public:
    DatabaseConnector();
    ~DatabaseConnector();

    bool connect();
    SQLHDBC getConnection() const;
    bool isConnected() const;
    void disconnect();

private:
    void showError() const;
};

#endif 