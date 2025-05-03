#include "DiscountStrategy.h"
#include <algorithm>


// Forward declarations of strategy implementations

PercentageDiscountStrategy::PercentageDiscountStrategy(int percentage) : percentage(percentage) {}

float PercentageDiscountStrategy::calculateDiscount(float total) const {
    return total * percentage / 100.0f;
}

std::string PercentageDiscountStrategy::getType() const {
    return "Percentage";
}

float PercentageDiscountStrategy::getValue() const {
    return static_cast<float>(percentage);
}

std::string PercentageDiscountStrategy::valueToString() const {
    return "P" + std::to_string(percentage);
}


FixedDiscountStrategy::FixedDiscountStrategy(int amount) : amount(amount) {}

float FixedDiscountStrategy::calculateDiscount(float total) const {
    return total < amount ? total : amount;
}

std::string FixedDiscountStrategy::getType() const {
    return "Fixed";
}

float FixedDiscountStrategy::getValue() const {
    return amount;
}

std::string FixedDiscountStrategy::valueToString() const {
    return "F" + std::to_string(amount);
}
