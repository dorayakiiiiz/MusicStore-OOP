/**
 * @file Cart.cpp
 * @brief Implementation file for the Cart class
 * 
 * @details Contains implementations for the shopping cart functionality,
 *          including adding, removing items and calculating totals
 */

#include "Cart.h"
#include <iostream>

// Add a music item to the cart with specified quantity
void Cart::addItems(Music item, int quantity) {
    item.updateQuantity(quantity);
    
    // Check if the item already exists in the cart
    for (int i = 0; i < _items.size(); ++i) {
        if (_items[i] == item) {
            // If found, update the quantity instead of adding a duplicate
            _items[i].updateQuantity(_items[i].getQuantity() + item.getQuantity());
            return;
        }
    }
    // If not found, add as a new item
    _items.push_back(item);
}

// Get the list of music items in the cart
const vector<Music>& Cart::getItems() const {
    return _items;
}

// Calculate the total price of all items in the cart
float Cart::calculateTotal() const {
    float total = 0;
    for (const auto& item : _items) {
        total += item.getPrice() * item.getQuantity();
    }
    return total;
}

// Remove an item from the cart by index
void Cart::removeItem(int id) {
    if (id < 0 || id >= _items.size()) {
        return;
    }
    _items.erase(_items.begin() + id);
}

// Clear all items from the cart
void Cart::clear() {
    _items.clear();
}