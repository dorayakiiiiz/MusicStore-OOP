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
Order::Order() : _username(""), _purchasedItems({}), _total(0.0f) {}

// Parameterized constructor - initializes an order with username, items, and total price
Order::Order(const string& username, const vector<Music>& items, const float& total) {
    this->_username = username;
    this->_total = total;

    // Copy all items to the purchasedItems vector
    for (const auto& item : items) {
        _purchasedItems.emplace_back(item);
    }
}

// Copy constructor - creates a new order by copying from another order object
Order::Order(const Order& other) 
    : _username(other._username), _purchasedItems(other._purchasedItems), _total(other._total) {}

// Get the total price of the order
float Order::getTotal() const {
    return _total;
}

// Get the username of the customer who placed the order
string Order::getUsername() const {
    return _username;
}

// Get the list of purchased music items
const vector<Music>& Order::getPurchasedItems() const {
    return _purchasedItems;
}
