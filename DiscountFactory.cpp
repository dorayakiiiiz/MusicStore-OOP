#include "DiscountFactory.h"


Discount* DiscountFactory::createDiscount(const std::string& type, float value) {
    if (type == "percentage") {
        return new PercentageDiscount(value);
    } else if (type == "fixed") {
        return new FixedAmountDiscount(value);
    }
    return nullptr;
}