#include "SalesRecordService.h"

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