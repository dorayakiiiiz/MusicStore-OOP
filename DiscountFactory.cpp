#include "DiscountFactory.h"

unique_ptr<Discount> DiscountFactory::createDiscount(const std::string& type, float value) {
    if (type == "percentage") {
        return make_unique<PercentageDiscount>(value);
    } else if (type == "fixed") {
        return make_unique<FixedAmountDiscount>(value);
    }
    return nullptr;
}

// commit