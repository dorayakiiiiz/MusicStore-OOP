#include "SQLSalesRecordRepository.h"

SqlSalesRecordRepository::SqlSalesRecordRepository() {}

SqlSalesRecordRepository::~SqlSalesRecordRepository() {}

std::vector<SalesRecord> SqlSalesRecordRepository::getAll() {
    vector<SalesRecord> salesRecord;

    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();

    if (!dbConnector->ensureConnected()) {
        return salesRecord;
    }
    // Implement here

    return salesRecord;

}

bool SqlSalesRecordRepository::add(const SalesRecord& record) {
    // Implement here
    return true;
}

bool SqlSalesRecordRepository::updateById(int id, const SalesRecord& record) { return false; }
bool SqlSalesRecordRepository::deleteById(int id) { return false; }