#include "SalesRecordService.h"

#include <memory>

using std::make_shared, std::vector, std::shared_ptr;

// Get the singleton instance of SalesRecordService
shared_ptr<SalesRecordService> SalesRecordService::getInstance() {
    if (instance == nullptr) {
        instance = make_shared<SalesRecordService>();
    }
    return instance;
}

// Get all sales records from the repository
vector<SalesRecord> SalesRecordService::getAllSalesRecords() {
    // Get all sales records from the repository
    auto dataProvider = make_shared<SqlDao>();
    return dataProvider->salesRecord()->getAll();
}

// add the items purchased to the sales record
void SalesRecordService::addToRecord(const Cart& cart) {
    auto dataProvider = make_shared<SqlDao>();
    // Add the items purchased to the sales record
    vector<Music> items = cart.getItems();
    for (int i = 0; i < items.size(); ++i) {
        SalesRecord salesRecord(items[i].getName(), items[i].getArtist(),
        items[i].getGenre(), items[i].getQuantity(), items[i].getPrice() * items[i].getQuantity());
        dataProvider->salesRecord()->add(salesRecord);
    }
}

// Get total revenue generated from all sales records
float SalesRecordService::getTotalRevenue() {
    // Get all sales records from the repository
    auto dataProvider = make_shared<SqlDao>();
    vector<SalesRecord> salesRecord = dataProvider->salesRecord()->getAll();
    // Calculate the total revenue
    float total = 0.0f;
    for (const auto& record : salesRecord) {
        total += record.getRevenue();
    }
    return total;
}
