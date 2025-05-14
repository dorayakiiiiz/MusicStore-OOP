// #include "SQLDiscountRepository.h"
// #include <memory>

// using std::make_shared, std::make_unique;

// SqlDiscountRepository::SqlDiscountRepository() {}

// SqlDiscountRepository::~SqlDiscountRepository() {}

// vector<Discount> SqlDiscountRepository::getAll() {
//     vector<Discount> vouchers;
    
//     if (!dbConnector.connect()) {
//         return vouchers;
//     }

//     SQLHSTMT hStmt = nullptr;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return vouchers;
//     }

//     std::string query = "SELECT Vouchername FROM vouchers";
//     SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);

//     if (SQL_SUCCEEDED(ret)) {
//         char voucherBuffer[256];
//         SQLLEN voucherLen;

//         SQLBindCol(hStmt, 1, SQL_C_CHAR, voucherBuffer, sizeof(voucherBuffer), &voucherLen);

//         while (SQL_SUCCEEDED(SQLFetch(hStmt))) {
//             std::string voucherString(voucherBuffer);
            
//             // Parse the voucher string and create Discount object
//             shared_ptr<Discount> discount = Discount::fromString(voucherString);
//             if (discount) {
//                 string username = discount->getUsername();
//                 string type = discount->getType();
//                 float value = discount->getValue();
                
//                 // Create appropriate discount strategy and add to vouchers
//                 if (type == "Percentage") {
//                     vouchers.push_back(Discount(username, make_unique<PercentageDiscountStrategy>(static_cast<int>(value))));
//                 } else if (type == "Fixed") {
//                     vouchers.push_back(Discount(username, make_unique<FixedDiscountStrategy>(static_cast<int>(value))));
//                 }
//             }
//         }
//     }

//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return vouchers;
// }

// bool SqlDiscountRepository::add(const Discount& discount) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     std::string query = "INSERT INTO vouchers (Vouchername) VALUES (?)";
//     SQLRETURN ret = SQLPrepare(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    
//     if (SQL_SUCCEEDED(ret)) {
//         std::string voucherString = discount.toString();
        
//         SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, voucherString.length(), 0, 
//                         (SQLCHAR*)voucherString.c_str(), voucherString.length(), NULL);
        
//         ret = SQLExecute(hStmt);
//         success = SQL_SUCCEEDED(ret);
//     }
    
//     SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//     dbConnector.disconnect();
    
//     return success;
// }

// bool SqlDiscountRepository::deleteById(int id) {
//     if (!dbConnector.connect()) {
//         return false;
//     }

//     SQLHSTMT hStmt = nullptr;
//     bool success = false;
    
//     if (SQLAllocHandle(SQL_HANDLE_STMT, dbConnector.getConnection(), &hStmt) != SQL_SUCCESS) {
//         dbConnector.disconnect();
//         return false;
//     }

//     std::string query = "DELETE FROM vouchers WHERE Id = ?";
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

