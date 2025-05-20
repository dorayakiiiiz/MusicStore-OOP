/**
 * @file DiscountService.cpp
 * @brief Implementation file for the DiscountService class
 * 
 * @details Contains implementations for managing discount vouchers, including
 *          creating, applying, and removing discounts
 */

#include "DiscountService.h"
#include "Discount.h"
#include "DiscountStrategy.h"
#include "Registry.h"
#include "IDiscountRepository.h"
#include <algorithm>

// Get all discount vouchers from the repository
vector<shared_ptr<Discount>> DiscountService::getAllDiscounts() {
    return Registry::getSingleton<IDiscountRepository>()->getAll();
}

// Apply a discount to a total price
float DiscountService::applyDiscount(const shared_ptr<Discount>& voucher, float total) {
    return voucher->apply(total);
}

// Check if a discount exists in the list of vouchers
bool DiscountService::isValidDiscount(const vector<shared_ptr<Discount>>& vouchers, 
                                     const shared_ptr<Discount>& voucher) {
    return any_of(vouchers.begin(), vouchers.end(), 
        [&](const shared_ptr<Discount>& v) {
            return v->toString() == voucher->toString();
        });
}

// Get all valid discounts for a specific username
vector<shared_ptr<Discount>> DiscountService::loadValidDiscounts(
    const vector<shared_ptr<Discount>>& vouchers, const string& username) {
    vector<shared_ptr<Discount>> validVouchers;
    
    for (const auto& voucher : vouchers) {
        if (voucher->getUsername() == username) {
            validVouchers.push_back(voucher);
        }
    }
    
    return validVouchers;
}

// Remove a discount voucher from the repository
void DiscountService::removeDiscount(const string& discountString) {
    // get all the vouchers from the repository
    vector<shared_ptr<Discount>> vouchers = Registry::getSingleton<IDiscountRepository>()->getAll();

    for (int i = 0; i < vouchers.size(); ++i) {
        if (vouchers[i]->toString() == discountString) {
            Registry::getSingleton<IDiscountRepository>()->deleteById(i + 1);
            break;
        }
    }
}

// Create a percentage discount voucher
shared_ptr<Discount> DiscountService::createPercentageDiscount(
    const string& username, int percentage) {
    return make_shared<Discount>(username, 
        make_unique<PercentageDiscountStrategy>(percentage));
}

// Create a fixed amount discount voucher
shared_ptr<Discount> DiscountService::createFixedDiscount(
    const string& username, float amount) {
    return make_shared<Discount>(username, 
        make_unique<FixedDiscountStrategy>(amount));
}

// Create a new discount voucher and add it to the repository
void DiscountService::createDiscount(const string& username, DiscountType type, int discountValue) {
    shared_ptr<Discount> discount;

    if (DiscountType::PERCENTAGE ==type) {
        discount = createPercentageDiscount(username, discountValue);
    } else if (DiscountType::FIXED_AMOUNT == type) {
        discount = createFixedDiscount(username, discountValue);
    }
    // Add the discount to the repository
    bool success = Registry::getSingleton<IDiscountRepository>()->add(discount);
    // fix heree
}