#include "SqlMusicRepository.h"

SqlMusicRepository::SqlMusicRepository() {}

SqlMusicRepository::~SqlMusicRepository() {}

std::vector<Music> SqlMusicRepository::getAll() {
    std::vector<Music> items;

    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    if (!dbConnector->ensureConnected()) return items;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return items;
    }

    std::string query = "SELECT NameSong, Artist, Genre, Price, Quantity FROM music_info";
    if (SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
        char tempName[256], tempArtist[256], tempGenre[100];
        float price;
        int quantity;

        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, tempName, sizeof(tempName), nullptr);
            SQLGetData(hStmt, 2, SQL_C_CHAR, tempArtist, sizeof(tempArtist), nullptr);
            SQLGetData(hStmt, 3, SQL_C_CHAR, tempGenre, sizeof(tempGenre), nullptr);
            SQLGetData(hStmt, 4, SQL_C_FLOAT, &price, 0, nullptr);
            SQLGetData(hStmt, 5, SQL_C_SLONG, &quantity, 0, nullptr);

            items.emplace_back(tempName, tempArtist, tempGenre, price, quantity);
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return items;
}

Music SqlMusicRepository::getById(int id) {
    Music music;

    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    if (!dbConnector->ensureConnected()) return music;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return music;
    }

    std::string query = "SELECT NameSong, Artist, Genre, Price, Quantity FROM music_info WHERE ID = ?";
    if (SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
        if (SQLExecute(hStmt) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
            char name[256], artist[256], genre[100];
            float price;
            int quantity;

            SQLGetData(hStmt, 1, SQL_C_CHAR, name, sizeof(name), nullptr);
            SQLGetData(hStmt, 2, SQL_C_CHAR, artist, sizeof(artist), nullptr);
            SQLGetData(hStmt, 3, SQL_C_CHAR, genre, sizeof(genre), nullptr);
            SQLGetData(hStmt, 4, SQL_C_FLOAT, &price, 0, nullptr);
            SQLGetData(hStmt, 5, SQL_C_SLONG, &quantity, 0, nullptr);

            music = Music(name, artist, genre, price, quantity);
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return music;
}

bool SqlMusicRepository::add(const Music& music) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) return false;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    std::string name = music.getName();
    std::string artist = music.getArtist();
    std::string genre = music.getGenre();
    float price = music.getPrice();
    int quantity = music.getQuantity();

    // Step 1: Check duplicates
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return false;
    }

    std::string checkQuery = "SELECT COUNT(*) FROM music_info WHERE NameSong = ? AND Artist = ?";
    ret = SQLPrepare(hStmt, (SQLCHAR*)checkQuery.c_str(), SQL_NTS);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, nullptr);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, nullptr);

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
        std::string idQuery = "SELECT ISNULL(MAX(ID), 0) + 1 FROM music_info";
        if (SQLExecDirect(hStmt, (SQLCHAR*)idQuery.c_str(), SQL_NTS) == SQL_SUCCESS && SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_SLONG, &newId, 0, nullptr);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    // Step 3: Insert
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return false;
    }

    std::string insertQuery = "INSERT INTO music_info (ID, NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?, ?)";
    SQLPrepare(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)name.c_str(), 0, nullptr);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, (SQLPOINTER)artist.c_str(), 0, nullptr);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)genre.c_str(), 0, nullptr);
    SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, &price, 0, nullptr);
    SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &quantity, 0, nullptr);

    bool success = SQL_SUCCEEDED(SQLExecute(hStmt));
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return success;
}

bool SqlMusicRepository::updateById(int id, const Music& music) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    // Step 1: Connect to the database
    if (!dbConnector->ensureConnected()) {
        return false;  // Connection failed
    }

    SQLHDBC hDbc = dbConnector->getConnection();  // Get DB connection handle
    SQLHSTMT hStmt = nullptr;                    // SQL statement handle
    SQLRETURN ret;                               // Return code
    bool success = false;                        // Result flag

    // Step 2: Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return false;
    }

    // Step 3: Prepare update query
    std::string updateQuery = "UPDATE music_info SET Price = ?, Quantity = ? WHERE ID = ?";
    ret = SQLPrepare(hStmt, (SQLCHAR*)updateQuery.c_str(), SQL_NTS);

    // Step 4: Bind parameters if query prepared successfully
    if (SQL_SUCCEEDED(ret)) {
        float price = music.getPrice();
        int quantity = music.getQuantity();

        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, &price, 0, nullptr);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &quantity, 0, nullptr);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);

        // Step 5: Execute update
        success = SQL_SUCCEEDED(SQLExecute(hStmt));
    }

    // Step 6: Clean up
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return success;
}

bool SqlMusicRepository::deleteById(int id) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) return false;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;

    // Step 1: Delete record
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return false;
    }

    std::string deleteQuery = "DELETE FROM music_info WHERE ID = ?";
    SQLPrepare(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS);
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
    bool success = SQL_SUCCEEDED(SQLExecute(hStmt));
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // Step 2: Shift IDs
    if (success && SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
        std::string selectQuery = "SELECT ID FROM music_info WHERE ID > ? ORDER BY ID ASC";
        SQLPrepare(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);

        if (SQLExecute(hStmt) == SQL_SUCCESS) {
            int currentId;
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_SLONG, &currentId, 0, nullptr);
                int newId = currentId - 1;

                SQLHSTMT hUpdateStmt = nullptr;
                if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hUpdateStmt) == SQL_SUCCESS) {
                    std::string updateQuery = "UPDATE music_info SET ID = ? WHERE ID = ?";
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
