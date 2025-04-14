#include "Cart.h"

void Cart::addItems(const MusicItem& item, int quantity) {
    for (auto& cartItem : items) {
        if (cartItem.first.getID() == item.getID()) {
            cartItem.second += quantity;
            return;
        }
    }
    items.emplace_back(item, quantity);
}

const vector<pair<MusicItem, int>>& Cart::getItems() const {
    return items;
}

float Cart::calculateTotal() const {
    float total = 0;
    for (const auto& [item, quantity] : items) {
        float price = item.getPrice();
        if (discount) {
            price = discount->applyDiscount(price);
        }
        total += price * quantity;
    }
    return total;
}

void Cart::removeItem(int id) {
    items.erase(items.begin() + id);
}

void Cart::applyDiscount(unique_ptr<Discount> discount) {
    this->discount = std::move(discount);
}

void Cart::clear() {
    items.clear();
}