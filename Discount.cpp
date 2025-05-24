/**
 * @file Discount.cpp
 * @brief Implementation file for the Discount classes
 * 
 * @details Contains implementations of the Discount base class and its derived
 *          classes for different discount types
 */

#include "Discount.h"
#include "DiscountStrategy.h"
#include <memory>
#include <stdexcept>

using std::string, std::unique_ptr, std::shared_ptr, std::move, std::exception, std::make_shared, std::make_unique;

// Constructor - creates a discount with a username and strategy
Discount::Discount(const string& code, const string& username, shared_ptr<DiscountStrategy> strategy)
    : code(code), username(username), strategy(move(strategy)) {}

// Get the discount code 
string Discount::getCode() const {
    return code;
}

// Apply the discount to a total price
float Discount::apply(float total) const {
    return total - strategy->calculateDiscount(total);
}

// Get the username this discount belongs to
string Discount::getUsername() const {
    return username;
}

// Get the type of discount (Percentage or Fixed Amount)
string Discount::getType() const {
    return strategy->getType();
}

// Get the value of the discount (percentage or amount)
float Discount::getValue() const {
    return strategy->getValue();
}

// Convert the discount to a string representation for storage
string Discount::toString() const {
    return code + " - " + strategy->toString();
}
