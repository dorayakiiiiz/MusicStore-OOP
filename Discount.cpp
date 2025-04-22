#include "Discount.h"

PercentageDiscount::PercentageDiscount(float percentage, const vector<string>& codes)
    : percentage(percentage), codes(codes) {}

float PercentageDiscount::applyDiscount(const float& price) const {
    return price * (1 - percentage / 100);
}

bool PercentageDiscount::isValidCode(const string& code) const {
    for (const auto& c : codes) {
        if (c == code) {
            return true;
        }
    }
    return false;
}

FixedAmountDiscount::FixedAmountDiscount(float amount, const vector<string>& codes)
    : amount(amount), codes(codes) {}

float FixedAmountDiscount::applyDiscount(const float& price) const {
    return price - amount > 0 ? price - amount : 0; 
}

bool FixedAmountDiscount::isValidCode(const string& code) const {
    for (const auto& c : codes) {
        if (c == code) {
            return true;
        }
    }
    return false;
}
