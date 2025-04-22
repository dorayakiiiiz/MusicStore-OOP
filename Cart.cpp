#include "Cart.h"

void Cart::addItems(const Music& item) {
    for (int i = 0; i < items.size(); ++i) {
        if (items[i] == item) {
            items[i].updateQuantity(items[i].getQuantity() + item.getQuantity());
            return;
        }
    }
    items.push_back(item);
}

const vector<Music>& Cart::getItems() const {
    return items;
}

float Cart::calculateTotal() const {
    float total = 0;
    for (const auto& item : items) {
        total += item.getPrice() * item.getQuantity();
    }
    return total;
}

void Cart::removeItem(int id) {
    if (id < 0 || id >= items.size()) {
        return;
    }
    items.erase(items.begin() + id);
}

void Cart::clear() {
    items.clear();
}