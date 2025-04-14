#include "Order.h"
#include <sstream>
using std::stringstream;
Order::Order(const string& id, const string& username, const vector<pair<int, int>>& items, const float& total) {
    this->username = username;
    this->total = total;
    this->orderId = id;

    for (const auto& [id, quantity] : items) {
        purchasedItems.emplace_back(id, quantity);
    }
}

string Order::getOrderId() const {
    return orderId;
}

float Order::getTotal() const {
    return total;
}

string Order::getUsername() const {
    return username;
}

const vector<pair<int, int>>& Order::getPurchasedItems() const {
    return purchasedItems;
}