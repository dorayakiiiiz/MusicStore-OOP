/**
 * @file Order.cpp
 * @brief Implementation file for the Order class
 * 
 * @details Contains implementations for order functionality including
 *          creation, item management and total calculation
 */

#include "Order.h"
#include <sstream>
using std::stringstream;

// Constructor - initializes an order with username, items, and total price
Order::Order(const string& username, const vector<Music>& items, const float& total) {
    this->username = username;
    this->total = total;

    // Copy all items to the purchasedItems vector
    for (const auto& item : items) {
        purchasedItems.emplace_back(item);
    }
}

// Get the total price of the order
float Order::getTotal() const {
    return total;
}

// Get the username of the customer who placed the order
string Order::getUsername() const {
    return username;
}

// Get the list of purchased music items
const vector<Music>& Order::getPurchasedItems() const {
    return purchasedItems;
}
