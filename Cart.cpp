#include "Cart.h"
#include <iostream>

void Cart::addItems(Music& item, int& quantity) {
    item.updateQuantity(quantity);
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

void Cart::displayCart() const {
    for (int i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << " - " << items[i].getName() << " - Quantity: " << items[i].getQuantity()
             << " - Price per unit: $" << items[i].getPrice()
             << " - Total: $" << items[i].getPrice() * items[i].getQuantity() << '\n';
    }
}