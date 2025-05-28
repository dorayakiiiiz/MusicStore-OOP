#include "SQLSalesRecordRepository.h"
#include "DatabaseConnector.h"
#include "../models/SalesRecord.h"
#include <vector>

using std::vector, std::string;

SqlSalesRecordRepository::SqlSalesRecordRepository() {}

SqlSalesRecordRepository::~SqlSalesRecordRepository() {}

std::vector<SalesRecord> SqlSalesRecordRepository::getAll() {
    vector<SalesRecord> salesRecord;
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    if (!dbConnector->ensureConnected()) {
        return salesRecord;
    }
    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return salesRecord;
    }

    string query = "SELECT NameSong, Artist, Genre, Sold, Revenue FROM sales_record";
    if (SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
        char tempName[256], tempArtist[256], tempGenre[100];
        int sold;
        float revenue;

        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempName, sizeof(tempName), nullptr);
            SQLGetData(hStmt, 2, SQL_C_CHAR, tempArtist, sizeof(tempArtist), nullptr);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempGenre, sizeof(tempGenre), nullptr);
            SQLGetData(hStmt, 4, SQL_C_SLONG, &sold, 0, nullptr);
            SQLGetData(hStmt, 5, SQL_C_FLOAT, &revenue, 0, nullptr);

            salesRecord.emplace_back(tempName, tempArtist, tempGenre, sold, revenue);
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return salesRecord;

}

bool SqlSalesRecordRepository::add(const SalesRecord& record) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) {
        return false;
    }
    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;
    bool success = false;

    string name = record.getName();
    string artist = record.getArtist();
    string genre = record.getGenre();
    int sold = record.getSold();
    float revenue = record.getRevenue();

    // Step 1: Check for duplicates
    int duplicate = 0;
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        string checkQuery = "SELECT COUNT(*) FROM sales_record WHERE NameSong = ? AND Artist = ?";
        ret = SQLPrepare(hStmt, (SQLCHAR*)checkQuery.c_str(), SQL_NTS);
        if (SQL_SUCCEEDED(ret)) {
            SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, nullptr);
            SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, nullptr);

            if (SQLExecute(hStmt) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_SLONG, &duplicate, 0, nullptr);
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    if (duplicate == 1) {
        // Step 2: Get existing sold and revenue, then update
        int sold_db = 0;
        float revenue_db = 0;

        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            string selectQuery = "SELECT Sold, Revenue FROM sales_record WHERE NameSong = ? AND Artist = ?";
            ret = SQLPrepare(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);
            if (SQL_SUCCEEDED(ret)) {
                SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, nullptr);
                SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, nullptr);

                if (SQLExecute(hStmt) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
                    SQLGetData(hStmt, 1, SQL_C_SLONG, &sold_db, 0, nullptr);
                    SQLGetData(hStmt, 2, SQL_C_FLOAT, &revenue_db, 0, nullptr);
                }
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }

        int newSold = sold + sold_db;
        float newRevenue = revenue + revenue_db;

        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            string updateQuery = "UPDATE sales_record SET Sold = ?, Revenue = ? WHERE NameSong = ? AND Artist = ?";
            ret = SQLPrepare(hStmt, (SQLCHAR*)updateQuery.c_str(), SQL_NTS);
            if (SQL_SUCCEEDED(ret)) {
                SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newSold, 0, nullptr);
                SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, &newRevenue, 0, nullptr);
                SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, nullptr);
                SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, nullptr);

                success = SQL_SUCCEEDED(SQLExecute(hStmt));
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
    } else {
        // Step 3: Insert new record
        int newId = 1;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            string idQuery = "SELECT ISNULL(MAX(ID), 0) + 1 FROM sales_record";
            if (SQLExecDirect(hStmt, (SQLCHAR*)idQuery.c_str(), SQL_NTS) == SQL_SUCCESS &&
                SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_SLONG, &newId, 0, nullptr);
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }

        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            string insertQuery = "INSERT INTO sales_record (ID, NameSong, Artist, Genre, Sold, Revenue) "
                                      "VALUES (?, ?, ?, ?, ?, ?)";
            ret = SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
            if (SQL_SUCCEEDED(ret)) {
                SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr);
                SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, nullptr);
                SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, nullptr);
                SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)genre.c_str(), 0, nullptr);
                SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sold, 0, nullptr);
                SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, &revenue, 0, nullptr);

                success = SQL_SUCCEEDED(SQLExecute(hStmt));
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
    }

    return success;
}

SalesRecord SqlSalesRecordRepository::getById(int id) {
    SalesRecord record;
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    if (!dbConnector->ensureConnected()) {
        return record;
    }
    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return record;
    }

    string query = "SELECT NameSong, Artist, Genre, Sold, Revenue FROM sales_record WHERE ID = ?";
    if (SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
        if (SQLExecute(hStmt) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
            char name[256], artist[256], genre[100];
            int sold;
            float revenue;

            SQLGetData(hStmt, 1, SQL_C_CHAR, name, sizeof(name), nullptr);
            SQLGetData(hStmt, 2, SQL_C_CHAR, artist, sizeof(artist), nullptr);
            SQLGetData(hStmt, 3, SQL_C_CHAR, genre, sizeof(genre), nullptr);
            SQLGetData(hStmt, 4, SQL_C_SLONG, &sold, 0, nullptr);
            SQLGetData(hStmt, 5, SQL_C_FLOAT, &revenue, 0, nullptr);

            record = SalesRecord(name, artist, genre, sold, revenue);
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return record;
}

// do nothing
bool SqlSalesRecordRepository::updateById(int id, const SalesRecord& record) { 
    return false; 
}

// do nothing
bool SqlSalesRecordRepository::deleteById(int id) { 
    return false; 
}