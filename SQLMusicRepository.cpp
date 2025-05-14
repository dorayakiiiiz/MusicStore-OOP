#include "SqlMusicRepository.h"

// sua cai nay

// SqlMusicRepository::SqlMusicRepository() {}

// SqlMusicRepository::~SqlMusicRepository() {}

// std::vector<Music> SqlMusicRepository::getAll() {
//     std::vector<Music> items;
    
//     // Connect to the database
//     if (!dbConnector.connect()) {
//         return items;
//     }

//     SQLHSTMT hStmt = nullptr;
    
//     // Allocate a statement handle
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return items;
//     }

//     // Execute query to get all music records
//     std::string query = "SELECT NameSong, Artist, Genre, Price, Quantity FROM music_info";
//     SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);

//     // Process query results
//     if (SQL_SUCCEEDED(ret)) {
//         char nameBuffer[256], artistBuffer[256], genreBuffer[100];
//         SQLLEN nameLen, artistLen, genreLen, priceLen, quantityLen;
//         float price;
//         int quantity;

//         // Bind columns
//         SQLBindCol(hStmt, 1, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), &nameLen);
//         SQLBindCol(hStmt, 2, SQL_C_CHAR, artistBuffer, sizeof(artistBuffer), &artistLen);
//         SQLBindCol(hStmt, 3, SQL_C_CHAR, genreBuffer, sizeof(genreBuffer), &genreLen);
//         SQLBindCol(hStmt, 4, SQL_C_FLOAT, &price, 0, &priceLen);
//         SQLBindCol(hStmt, 5, SQL_C_LONG, &quantity, 0, &quantityLen);

//         // Fetch rows
//         while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
//             items.emplace_back(
//                 std::string(nameBuffer),
//                 std::string(artistBuffer),
//                 std::string(genreBuffer),
//                 price,
//                 quantity
//             );
//         }
//     }

//     // Clean up
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return items;
// }

// Music SqlMusicRepository::getById(int id) {
//     Music music;
    
//     if (!dbConnector.connect()) {
//         return music;
//     }

//     SQLHSTMT hStmt = nullptr;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return music;
//     }

//     std::string query = "SELECT NameSong, Artist, Genre, Price, Quantity FROM music_info WHERE Id = ?";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         // Bind parameters
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, NULL);
        
//         ret = SQLExecute(hStmt);
        
//         if (SQL_SUCCEEDED(ret)) {
//             char nameBuffer[256], artistBuffer[256], genreBuffer[100];
//             SQLLEN nameLen, artistLen, genreLen, priceLen, quantityLen;
//             float price;
//             int quantity;

//             // Bind columns
//             SQLBindCol(hStmt, 1, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), &nameLen);
//             SQLBindCol(hStmt, 2, SQL_C_CHAR, artistBuffer, sizeof(artistBuffer), &artistLen);
//             SQLBindCol(hStmt, 3, SQL_C_CHAR, genreBuffer, sizeof(genreBuffer), &genreLen);
//             SQLBindCol(hStmt, 4, SQL_C_FLOAT, &price, 0, &priceLen);
//             SQLBindCol(hStmt, 5, SQL_C_LONG, &quantity, 0, &quantityLen);

//             // Fetch the row
//             if (SQL_SUCCEEDED(SQLFetch(hStmt))) {
//                 music = Music(
//                     std::string(nameBuffer),
//                     std::string(artistBuffer),
//                     std::string(genreBuffer),
//                     price,
//                     quantity
//                 );
//             }
//         }
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return music;
// }

// bool SqlMusicRepository::add(const Music& music) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     std::string query = "INSERT INTO music_info (NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?)";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         // Get music attributes
//         std::string name = music.getName();
//         std::string artist = music.getArtist();
//         std::string genre = music.getGenre();
//         float price = music.getPrice();
//         int quantity = music.getQuantity();
        
//         // Bind parameters
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.length(), 0, 
//                         (SQLCHAR*)name.c_str(), name.length(), NULL);
//         SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, artist.length(), 0, 
//                         (SQLCHAR*)artist.c_str(), artist.length(), NULL);
//         SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, genre.length(), 0, 
//                         (SQLCHAR*)genre.c_str(), genre.length(), NULL);
//         SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, 
//                         &price, 0, NULL);
//         SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, 
//                         &quantity, 0, NULL);
        
//         ret = SQLExecute(hStmt);
//         success = SQL_SUCCEEDED(ret);
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return success;
// }

// bool SqlMusicRepository::updateById(int id, const Music& music) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     std::string query = "UPDATE music_info SET NameSong = ?, Artist = ?, Genre = ?, Price = ?, Quantity = ? WHERE Id = ?";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         // Get music attributes
//         std::string name = music.getName();
//         std::string artist = music.getArtist();
//         std::string genre = music.getGenre();
//         float price = music.getPrice();
//         int quantity = music.getQuantity();
        
//         // Bind parameters
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.length(), 0, 
//                         (SQLCHAR*)name.c_str(), name.length(), NULL);
//         SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, artist.length(), 0, 
//                         (SQLCHAR*)artist.c_str(), artist.length(), NULL);
//         SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, genre.length(), 0, 
//                         (SQLCHAR*)genre.c_str(), genre.length(), NULL);
//         SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, 
//                         &price, 0, NULL);
//         SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, 
//                         &quantity, 0, NULL);
//         SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, 
//                         &id, 0, NULL);
        
//         ret = SQLExecute(hStmt);
//         success = SQL_SUCCEEDED(ret);
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return success;
// }

// bool SqlMusicRepository::deleteById(int id) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     std::string query = "DELETE FROM music_info WHERE Id = ?";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         // Bind parameter
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, NULL);
        
//         ret = SQLExecute(hStmt);
//         success = SQL_SUCCEEDED(ret);
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return success;
// }

