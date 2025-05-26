/**
 * @file DiscountStrategy.cpp
 * @brief Implementation file for discount strategy classes
 * 
 * @details Contains implementations of different discount calculation
 *          strategies used by the discount system
 */

#include "DiscountStrategy.h"
#include <algorithm>

using std::to_string;


// Forward declarations of strategy implementations

PercentageDiscountStrategy::PercentageDiscountStrategy(int percentage) : percentage(percentage) {}

float PercentageDiscountStrategy::calculateDiscount(float total) const {
    return total * percentage / 100.0f;
}

string PercentageDiscountStrategy::getType() const {
    return "Percentage";
}

int PercentageDiscountStrategy::getValue() const {
    return percentage;
}

void PercentageDiscountStrategy::setValue(int value) {
    percentage = value; 
}

string PercentageDiscountStrategy::toString() const {
    return "Percentage discount: " + to_string(percentage) + "%";
}


FixedDiscountStrategy::FixedDiscountStrategy(int amount) : amount(amount) {}

float FixedDiscountStrategy::calculateDiscount(float total) const {
    return total < amount ? total : amount;
}

string FixedDiscountStrategy::getType() const {
    return "Fixed";
}

int FixedDiscountStrategy::getValue() const {
    return amount;
}

void FixedDiscountStrategy::setValue(int value) {
    amount = value; 
}

string FixedDiscountStrategy::toString() const {
    return "Fixed discount: " + to_string(amount) + "$";
}

