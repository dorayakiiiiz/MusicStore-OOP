#include "DiscountFactory.h"
#include <algorithm>

// Apply a discount to a total price and return the discounted amount
float DiscountFactory::applyDiscount(shared_ptr<IDiscount> voucher, float total) {
    string type = voucher->getType();
    if (type == "Percentage") {
        // Calculate percentage discount (e.g., 10% off)
        return total - (total * (voucher->getDiscountValue() / 100));
    } else if (type == "Fixed Amount") {
        // Apply fixed amount discount (e.g., $5 off)
        return total - voucher->getDiscountValue();
    }
    return total;
}

// Check if a discount exists in the list of vouchers
bool DiscountFactory::isValidDiscount(vector<shared_ptr<IDiscount>> vouchers, shared_ptr<IDiscount> voucher) {
    for (const auto& v : vouchers) {
        if (v->toString() == voucher->toString()) {
            return true;
        }
    }
    return false;
}

// Get all valid discounts for a specific username
vector<shared_ptr<IDiscount>> DiscountFactory::loadValidDiscounts(const vector<shared_ptr<IDiscount>>& vouchers, const string& username) {
    vector<shared_ptr<IDiscount>> validVouchers;
    for (const auto& voucher : vouchers) {
        if (voucher->getUsername() == username) {
            validVouchers.push_back(voucher);
        }
    }
    return validVouchers;
}

// Remove a specific discount from the list using its code
void DiscountFactory::removeDiscount(vector<shared_ptr<IDiscount>>& vouchers, const string& code) {
    for (int i = 0; i < vouchers.size(); ++i) {
        if (vouchers[i]->toString() == code) {
            vouchers.erase(vouchers.begin() + i);
            break;
        }
    }
}