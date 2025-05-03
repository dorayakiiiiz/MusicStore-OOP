#include "DiscountService.h"
#include "Discount.h"
#include "DiscountStrategy.h"
#include <algorithm>


float DiscountService::applyDiscount(const shared_ptr<Discount>& voucher, float total) {
    return voucher->apply(total);
}

bool DiscountService::isValidDiscount(const vector<shared_ptr<Discount>>& vouchers, 
                                     const shared_ptr<Discount>& voucher) {
    return any_of(vouchers.begin(), vouchers.end(), 
        [&](const shared_ptr<Discount>& v) {
            return v->toString() == voucher->toString();
        });
}

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

void DiscountService::removeDiscount(vector<shared_ptr<Discount>>& vouchers, 
                                    const string& discountString) {
    auto it = remove_if(vouchers.begin(), vouchers.end(),
        [&](const shared_ptr<Discount>& voucher) {
            return voucher->toString() == discountString;
        });
    
    if (it != vouchers.end()) {
        vouchers.erase(it, vouchers.end());
    }
}

shared_ptr<Discount> DiscountService::createPercentageDiscount(
    const string& username, int percentage) {
    return make_shared<Discount>(username, 
        make_unique<PercentageDiscountStrategy>(percentage));
}

shared_ptr<Discount> DiscountService::createFixedDiscount(
    const string& username, float amount) {
    return make_shared<Discount>(username, 
        make_unique<FixedDiscountStrategy>(amount));
}

void DiscountService::createDiscount(vector<shared_ptr<Discount>>& vouchers, 
    const string& username, int discountType, int discountValue) {
    if (discountType == 1) {
        vouchers.push_back(createPercentageDiscount(username, discountValue));
    } else if (discountType == 2) {
        vouchers.push_back(createFixedDiscount(username, discountValue));
    }
}