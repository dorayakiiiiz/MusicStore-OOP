#include "SalesRecordService.h"

#include <memory>

using std::make_shared, std::vector, std::shared_ptr;

// Constructor
SalesRecordService::SalesRecordService(shared_ptr<IDataProvider> provider) {
    this->dataProvider = provider;
}

// Get the singleton instance of SalesRecordService
shared_ptr<SalesRecordService> SalesRecordService::getInstance(shared_ptr<IDataProvider> provider) {
    if (instance == nullptr) {
        // If no provider is passed, use the default SqlDao
        if (!provider) {
            provider = make_shared<SqlDao>();
        }
        instance = shared_ptr<SalesRecordService>(new SalesRecordService(provider));
    }
    return instance;
}

// Get all sales records from the repository
vector<SalesRecord> SalesRecordService::getAllSalesRecords() {
    return dataProvider->salesRecord()->getAll();
}

// Add the items purchased to the sales record
void SalesRecordService::addToRecord(const Cart& cart) {
    vector<Music> items = cart.getItems();
    for (int i = 0; i < items.size(); ++i) {
        SalesRecord salesRecord(items[i].getName(), items[i].getArtist(),
        items[i].getGenre(), items[i].getQuantity(), items[i].getPrice() * items[i].getQuantity());
        dataProvider->salesRecord()->add(salesRecord);
    }
}

// Get total revenue generated from all sales records
float SalesRecordService::getTotalRevenue() {
    vector<SalesRecord> salesRecord = dataProvider->salesRecord()->getAll();
    // Calculate the total revenue
    float total = 0.0f;
    for (const auto& record : salesRecord) {
        total += record.getRevenue();
    }
    return total;
}
