/**
 * @file Discount.cpp
 * @brief Implementation file for the Discount classes
 * 
 * @details Contains implementations of the Discount base class and its derived
 *          classes for different discount types
 */

#include "../models/Discount.h"
#include <memory>
#include <stdexcept>

using std::string, std::unique_ptr, std::shared_ptr, std::move, std::exception, std::make_shared, std::make_unique;

// Constructor - creates a discount with a username and strategy
Discount::Discount(const string& code, const string& username, shared_ptr<DiscountStrategy> strategy)
    : _code(code), _username(username), _strategy(move(strategy)) {}

// Get the discount code 
string Discount::getCode() const {
    return _code;
}

// Apply the discount to a total price
float Discount::apply(float total) const {
    return total - _strategy->calculateDiscount(total) ? total - _strategy->calculateDiscount(total) : 0.0f; // Ensure total doesn't go negative
}

// Get the username this discount belongs to
string Discount::getUsername() const {
    return _username;
}

// Get the type of discount (Percentage or Fixed Amount)
string Discount::getType() const {
    return _strategy->getType();
}

// Get the value of the discount (percentage or amount)
float Discount::getValue() const {
    return _strategy->getValue();
}

// Convert the discount to a string representation for storage
string Discount::toString() const {
    return _code + " (" + _strategy->toString() + ")";
}