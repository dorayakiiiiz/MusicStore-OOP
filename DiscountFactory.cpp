#include "DiscountFactory.h"

DiscountFactory::DiscountFactory() {
    // Initialize the discount strategies
    strategies[DiscountType::PERCENTAGE] = make_shared<PercentageDiscountStrategy>(0);
    strategies[DiscountType::FIXED_AMOUNT] = make_shared<FixedDiscountStrategy>(0);
}

shared_ptr<DiscountStrategy> DiscountFactory::getStrategy(DiscountType type) {
    auto it = strategies.find(type);
    if (it != strategies.end()) {
        return it->second; // Return the strategy for the requested type
    }
    return nullptr; // Return null if type not found
}