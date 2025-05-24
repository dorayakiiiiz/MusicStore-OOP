#include "SQLDiscountRepository.h"
#include <memory>

using std::make_shared, std::make_unique;

SqlDiscountRepository::SqlDiscountRepository() {}

SqlDiscountRepository::~SqlDiscountRepository() {}

vector<shared_ptr<Discount>> SqlDiscountRepository::getAll() {
    vector<shared_ptr<Discount>> vouchers;  // Container for discount vouchers

    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    // Step 1: Connect to the database
    if (!dbConnector->ensureConnected()) {
        return vouchers;  // Return empty vector if connection fails
    }

    SQLHDBC hDbc = dbConnector->getConnection();  // Get database connection handle
    SQLHSTMT hStmt = nullptr;                    // SQL statement handle
    SQLRETURN ret;                               // SQL operation return value

    // Step 2: Allocate a statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        return vouchers;  // Return empty vector if handle allocation fails
    }

    // gồm id, code, username, type (char(1): P hoặc F), value
    // id và type để xét trong database chứ ko có lưu vô biến Discount
    char type; string code, username; int value;
    // sửa tại đây-------------------

    
    // tới đây-----------------

    // dòng này cho m hiểu cấu trúc
    shared_ptr<Discount> voucher;
    if (type == 'F') {
        voucher = std::make_shared<Discount>(code, username, make_unique<FixedDiscountStrategy>(value));
    } else {
        voucher = std::make_shared<Discount>(code, username, make_unique<PercentageDiscountStrategy>(value));
    }
    vouchers.push_back(voucher);
    // đoạn code nài phải sửa lại chèn đúng vô code m



    // Step 5: Clean up resources
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return vouchers;  // Return the populated vector
}

bool SqlDiscountRepository::add(const shared_ptr<Discount>& discount) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) return false;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;
    SQLRETURN ret;

    // cài lại ở đây
    // tự tạo id như cũ
    // lấy các thông tin code, username, type, value như sau:
    string username = discount->getUsername();
    char type = discount->getType()[0]; 
    string code = discount->getCode();
    int value = discount->getValue();
    // sửa lại rồi add vào

    return true;
}

bool SqlDiscountRepository::deleteById(int id) {
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    if (!dbConnector->ensureConnected()) return false;

    SQLHDBC hDbc = dbConnector->getConnection();
    SQLHSTMT hStmt = nullptr;
    bool success = false;

    // Tắt autocommit để dùng transaction
    SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);

    do {
        // Bước 1: Xóa bản ghi
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) break;

        std::string deleteQuery = "DELETE FROM vouchers WHERE ID = ?";
        if (SQLPrepare(hStmt, (SQLCHAR*)deleteQuery.c_str(), SQL_NTS) != SQL_SUCCESS) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }
        if (SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr) != SQL_SUCCESS) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }
        if (!SQL_SUCCEEDED(SQLExecute(hStmt))) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Bước 2: Lấy các ID lớn hơn ID bị xóa
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) break;

        std::string selectQuery = "SELECT ID FROM vouchers WHERE ID > ? ORDER BY ID ASC";
        if (SQLPrepare(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS) != SQL_SUCCESS) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }
        if (SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, nullptr) != SQL_SUCCESS) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }
        if (SQLExecute(hStmt) != SQL_SUCCESS) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            break;
        }

        std::vector<int> idsToUpdate;
        int currentId;
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            if (SQLGetData(hStmt, 1, SQL_C_SLONG, &currentId, 0, nullptr) == SQL_SUCCESS) {
                idsToUpdate.push_back(currentId);
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Bước 3: Cập nhật ID giảm đi 1 theo thứ tự
        for (int oldId : idsToUpdate) {
            int tmpId = -oldId;    // chuyển sang âm để tránh trùng
            int newId = oldId - 1;

            // Cập nhật sang tmpId âm
            if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) break;

            std::string updateTmpQuery = "UPDATE vouchers SET ID = ? WHERE ID = ?";
            if (SQLPrepare(hStmt, (SQLCHAR*)updateTmpQuery.c_str(), SQL_NTS) != SQL_SUCCESS) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            if (SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &tmpId, 0, nullptr) != SQL_SUCCESS) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            if (SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &oldId, 0, nullptr) != SQL_SUCCESS) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            if (!SQL_SUCCEEDED(SQLExecute(hStmt))) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

            // Cập nhật từ tmpId âm sang newId dương
            if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) break;

            std::string updateNewQuery = "UPDATE vouchers SET ID = ? WHERE ID = ?";
            if (SQLPrepare(hStmt, (SQLCHAR*)updateNewQuery.c_str(), SQL_NTS) != SQL_SUCCESS) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            if (SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newId, 0, nullptr) != SQL_SUCCESS) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            if (SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &tmpId, 0, nullptr) != SQL_SUCCESS) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            if (!SQL_SUCCEEDED(SQLExecute(hStmt))) {
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
                break;
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }

        success = true;

    } while(false);

    // Commit hoặc rollback transaction
    if (success) {
        SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_COMMIT);
    } else {
        SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK);
    }

    // Bật lại autocommit
    SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, 0);

    return success;
}

// Các hàm không dùng vẫn giữ nguyên
bool SqlDiscountRepository::updateById(int id, const shared_ptr<Discount>& discount) { return false; }
shared_ptr<Discount> SqlDiscountRepository::getById(int id) { return nullptr; }
