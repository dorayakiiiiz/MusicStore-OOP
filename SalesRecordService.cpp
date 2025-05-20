#include "SalesRecordService.h"

// Get all sales records from the repository
vector<SalesRecord> SalesRecordService::getAllSalesRecords() {
    // Get all sales records from the repository
    auto salesRecordRepo = Registry::getSingleton<ISalesRecordRepository>();
    return salesRecordRepo->getAll();
}

// add the items purchased to the sales record
void SalesRecordService::addToRecord(const Cart& cart) {
    auto salesRecordRepo = Registry::getSingleton<ISalesRecordRepository>();
    // Add the items purchased to the sales record
    vector<Music> items = cart.getItems();
    for (int i = 0; i < items.size(); ++i) {
        SalesRecord salesRecord(items[i].getName(), items[i].getArtist(),
        items[i].getGenre(), items[i].getQuantity(), items[i].getPrice() * items[i].getQuantity());
        salesRecordRepo->add(salesRecord);
    }
}

// Get total revenue generated from all sales records
float SalesRecordService::getTotalRevenue() {
    // Get all sales records from the repository
    vector<SalesRecord> salesRecord = Registry::getSingleton<ISalesRecordRepository>()->getAll();
    // Calculate the total revenue
    float total = 0.0f;
    for (const auto& record : salesRecord) {
        total += record.getRevenue();
    }
    return total;
}
