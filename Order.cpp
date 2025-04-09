#include "Order.h"

Order::Order(const vector<MusicItem>& items, float total) {
    this->items = items;
    this->total = total;
}

string Order::getOrderId() const {
    return orderId;
}

float Order::getTotal() const {
    return total;
}