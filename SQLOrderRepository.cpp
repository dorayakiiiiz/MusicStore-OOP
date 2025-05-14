#include "SQLOrderRepository.h"

// sua cai nay

// SqlOrderRepository::SqlOrderRepository() {}

// SqlOrderRepository::~SqlOrderRepository() {}

// vector<Order> SqlOrderRepository::getAll() {
//     vector<Order> orders;
    
//     if (!dbConnector.connect()) {
//         return orders;
//     }

//     SQLHSTMT hStmt = nullptr;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return orders;
//     }

//     // Complex query to get order header and details together
//     std::string query = R"(
//         SELECT o.Username, o.TotalPrice, d.NameSong, d.Artist, d.Genre, d.Price, d.Quantity, o.OrderCode
//         FROM orders o
//         JOIN detail_order d ON o.OrderCode = d.OrderCode
//         ORDER BY o.OrderCode
//     )";
    
//     SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);

//     if (SQL_SUCCEEDED(ret)) {
//         char usernameBuffer[100], nameSongBuffer[256], artistBuffer[256], genreBuffer[100];
//         SQLLEN usernameLen, nameSongLen, artistLen, genreLen, priceLen, quantityLen, totalPriceLen, orderCodeLen;
//         float price, totalPrice;
//         int quantity, currentOrderCode = -1, orderCode;
//         std::string currentUsername;
//         vector<Music> currentItems;
        
//         // Bind columns
//         SQLBindCol(hStmt, 1, SQL_C_CHAR, usernameBuffer, sizeof(usernameBuffer), &usernameLen);
//         SQLBindCol(hStmt, 2, SQL_C_FLOAT, &totalPrice, 0, &totalPriceLen);
//         SQLBindCol(hStmt, 3, SQL_C_CHAR, nameSongBuffer, sizeof(nameSongBuffer), &nameSongLen);
//         SQLBindCol(hStmt, 4, SQL_C_CHAR, artistBuffer, sizeof(artistBuffer), &artistLen);
//         SQLBindCol(hStmt, 5, SQL_C_CHAR, genreBuffer, sizeof(genreBuffer), &genreLen);
//         SQLBindCol(hStmt, 6, SQL_C_FLOAT, &price, 0, &priceLen);
//         SQLBindCol(hStmt, 7, SQL_C_LONG, &quantity, 0, &quantityLen);
//         SQLBindCol(hStmt, 8, SQL_C_LONG, &orderCode, 0, &orderCodeLen);

//         // Fetch rows
//         while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
//             // If we're starting a new order
//             if (orderCode != currentOrderCode) {
//                 // If this isn't the first order, add the previous one to our result
//                 if (currentOrderCode != -1) {
//                     orders.emplace_back(currentUsername, currentItems, totalPrice);
//                     currentItems.clear();
//                 }
                
//                 currentOrderCode = orderCode;
//                 currentUsername = std::string(usernameBuffer);
//             }
            
//             // Add the current item to the current order
//             currentItems.emplace_back(
//                 std::string(nameSongBuffer),
//                 std::string(artistBuffer),
//                 std::string(genreBuffer),
//                 price,
//                 quantity
//             );
//         }
        
//         // Add the last order if we processed any rows
//         if (currentOrderCode != -1) {
//             orders.emplace_back(currentUsername, currentItems, totalPrice);
//         }
//     }

//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return orders;
// }

// bool SqlOrderRepository::add(const Order& order) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     // First, insert into orders table
//     std::string orderQuery = "INSERT INTO orders (Username, TotalPrice) VALUES (?, ?); SELECT SCOPE_IDENTITY() AS OrderId";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)orderQuery.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         std::string username = order.getUsername();
//         float totalPrice = order.getTotal();
        
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, 
//                         (SQLCHAR*)username.c_str(), username.length(), NULL);
//         SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, 
//                         (float*)&totalPrice, 0, NULL);
        
//         ret = SQLExecute(hStmt);
        
//         // Get the inserted order ID
//         int orderId = 0;
//         if (SQL_SUCCEEDED(ret) && SQL_SUCCEEDED(SQLFetch(hStmt))) {
//             SQLGetData(hStmt, 1, SQL_C_LONG, &orderId, 0, NULL);
            
//             // Now insert order details
//             SQLFreeStmt(hStmt, SQL_CLOSE);
            
//             const vector<Music>& items = order.getPurchasedItems();
//             for (const auto& item : items) {
//                 std::string detailQuery = "INSERT INTO detail_order (OrderCode, NameSong, Artist, Genre, Price, Quantity) VALUES (?, ?, ?, ?, ?, ?)";
//                 ret = SQLPrepare(hStmt, (SQLCHAR*)detailQuery.c_str(), SQL_NTS);
                
//                 if (SQL_SUCCEEDED(ret)) {
//                     std::string name = item.getName();
//                     std::string artist = item.getArtist();
//                     std::string genre = item.getGenre();
//                     float price = item.getPrice();
//                     int quantity = item.getQuantity();
                    
//                     SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, 
//                                     &orderId, 0, NULL);
//                     SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.length(), 0, 
//                                     (SQLCHAR*)name.c_str(), name.length(), NULL);
//                     SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, artist.length(), 0, 
//                                     (SQLCHAR*)artist.c_str(), artist.length(), NULL);
//                     SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, genre.length(), 0, 
//                                     (SQLCHAR*)genre.c_str(), genre.length(), NULL);
//                     SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, 
//                                     (float*)&price, 0, NULL);
//                     SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, 
//                                     (int*)&quantity, 0, NULL);
                    
//                     ret = SQLExecute(hStmt);
//                     SQLFreeStmt(hStmt, SQL_CLOSE);
                    
//                     if (!SQL_SUCCEEDED(ret)) {
//                         break;
//                     }
//                 }
//             }
            
//             success = SQL_SUCCEEDED(ret);
//         }
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return success;
// }
