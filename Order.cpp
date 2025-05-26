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

// Default constructor - creates an empty order
Order::Order() : username(""), purchasedItems({}), total(0.0f) {}

// Parameterized constructor - initializes an order with username, items, and total price
Order::Order(const string& username, const vector<Music>& items, const float& total) {
    this->username = username;
    this->total = total;

    // Copy all items to the purchasedItems vector
    for (const auto& item : items) {
        purchasedItems.emplace_back(item);
    }
}

// Copy constructor - creates a new order by copying from another order object
Order::Order(const Order& other) 
    : username(other.username), purchasedItems(other.purchasedItems), total(other.total) {}

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
