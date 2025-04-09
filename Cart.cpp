#include "Cart.h"

void Cart::addItems(const MusicItem& item) {
    items.push_back(item);
}

const vector<MusicItem>& Cart::getItems() const {
    return items;
}

float Cart::calculateTotal() const {
    float total = 0;
    for (int i = 0; i < items.size(); ++i) {
        total += discount ? discount->applyDiscount(items[i].getPrice()) : items[i].getPrice();
    }
    return total;
}

void Cart::removeItem(int id) {
    items.erase(items.begin() + id);
}

void Cart::applyDiscount(Discount* discount) {
    if (this->discount != nullptr) {
        delete this->discount;
    }
    this->discount = discount;
}