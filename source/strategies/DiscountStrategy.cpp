/**
 * @file DiscountStrategy.cpp
 * @brief Implementation file for discount strategy classes
 * 
 * @details Contains implementations of different discount calculation
 *          strategies used by the discount system
 */

#include "DiscountStrategy.h"
#include <string>
#include <sstream>
#include <algorithm>

using std::to_string;


// Forward declarations of strategy implementations

PercentageDiscountStrategy::PercentageDiscountStrategy(int percentage) : _percentage(percentage) {}

float PercentageDiscountStrategy::calculateDiscount(float total) const {
    return total * _percentage / 100.0f;
}

string PercentageDiscountStrategy::getType() const {
    return "Percentage";
}

int PercentageDiscountStrategy::getValue() const {
    return _percentage;
}

void PercentageDiscountStrategy::setValue(int value) {
    _percentage = value; 
}

string PercentageDiscountStrategy::toString() const {
    return "Percentage discount: " + to_string(_percentage) + "%";
}


FixedDiscountStrategy::FixedDiscountStrategy(int amount) : _amount(amount) {}

float FixedDiscountStrategy::calculateDiscount(float total) const {
    return total < _amount ? total : _amount;
}

string FixedDiscountStrategy::getType() const {
    return "Fixed";
}

int FixedDiscountStrategy::getValue() const {
    return _amount;
}

void FixedDiscountStrategy::setValue(int value) {
    _amount = value; 
}

string FixedDiscountStrategy::toString() const {
    return "Fixed discount: " + to_string(_amount) + "$";
}