#include "Discount.h"

PercentageDiscount::PercentageDiscount(const float& perc) {
    this->percentage = perc;
}

float PercentageDiscount::applyDiscount(const float& price) {
    return price * (1 - percentage / 100);
}

FixedAmountDiscount::FixedAmountDiscount(const float& amo) {
    this->amount = amo;
}

float FixedAmountDiscount::applyDiscount(const float& price) {
    return price - amount;
}
    