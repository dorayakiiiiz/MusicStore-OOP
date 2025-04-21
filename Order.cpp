#include "Order.h"
#include <sstream>
using std::stringstream;
Order::Order(const string& username, const vector<MusicItem>& items, const float& total) {
    this->username = username;
    this->total = total;

    for (const auto& item : items) {
        purchasedItems.emplace_back(item);
    }
}


float Order::getTotal() const {
    return total;
}

string Order::getUsername() const {
    return username;
}

const vector<MusicItem>& Order::getPurchasedItems() const {
    return purchasedItems;
}