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
#include "IDataProvider.h"
#include "SQLDao.h"
#include <algorithm>

// Constructor
DiscountService::DiscountService() {
    dataProvider = make_shared<SqlDao>();
}

// Get the singleton instance of DiscountService
shared_ptr<DiscountService> DiscountService::getInstance() {
    if (instance == nullptr) {
        instance = shared_ptr<DiscountService>(new DiscountService());
    }
    return instance;
}

// Get all discount vouchers from the repository
vector<shared_ptr<Discount>> DiscountService::getAllDiscounts() {
    return dataProvider->discount()->getAll();
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
void DiscountService::removeDiscount(const shared_ptr<Discount>& discount) {
    // get all the vouchers from the repository
    vector<shared_ptr<Discount>> vouchers = dataProvider->discount()->getAll();

    for (int i = 0; i < vouchers.size(); ++i) {
        if (vouchers[i]->getCode() == discount->getCode()) {
            dataProvider->discount()->deleteById(i + 1);
            break;
        }
    }
}

// Generate a random discount code
string DiscountService::generateRandomCode() {
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string code;
    srand(time(NULL));
    for (int i = 0; i < 6; ++i) {
        int index = rand() % characters.size();
        code += characters[index];
    }
    return code;
}


// Create a new discount voucher and add it to the repository
void DiscountService::createDiscount(const string& username, DiscountType type, int discountValue) {
    shared_ptr<Discount> discount;

    string code = generateRandomCode();

    if (DiscountType::PERCENTAGE == type) {
        discount = make_shared<Discount>(code, username, make_unique<PercentageDiscountStrategy>(discountValue));
    } else if (DiscountType::FIXED_AMOUNT == type) {
        discount = make_shared<Discount>(code, username,  make_unique<FixedDiscountStrategy>(discountValue));
    }

    // Add the discount to the repository
    bool success = dataProvider->discount()->add(discount);
    // fix heree
}