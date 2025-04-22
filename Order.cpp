#include "Order.h"
#include <sstream>
using std::stringstream;
Order::Order(const string& username, const vector<Music>& items, const float& total) {
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

const vector<Music>& Order::getPurchasedItems() const {
    return purchasedItems;
}