#include "DiscountFactory.h"
#include <algorithm>

float DiscountFactory::applyDiscount(shared_ptr<IDiscount> voucher, float total) {
    string type = voucher->getType();
    if (type == "Percentage") {
        return total - (total * (voucher->getDiscountValue() / 100));
    } else if (type == "Fixed Amount") {
        return total - voucher->getDiscountValue();
    }
    return total;
}

bool DiscountFactory::isValidDiscount(vector<shared_ptr<IDiscount>> vouchers, shared_ptr<IDiscount> voucher) {
    for (const auto& v : vouchers) {
        if (v->toString() == voucher->toString()) {
            return true;
        }
    }
    return false;
}

vector<shared_ptr<IDiscount>> DiscountFactory::loadValidDiscounts(const vector<shared_ptr<IDiscount>>& vouchers, const string& username) {
    vector<shared_ptr<IDiscount>> validVouchers;
    for (const auto& voucher : vouchers) {
        if (voucher->getUsername() == username) {
            validVouchers.push_back(voucher);
        }
    }
    return validVouchers;
}

void DiscountFactory::removeDiscount(vector<shared_ptr<IDiscount>>& vouchers, const string& code) {
    for (int i = 0; i < vouchers.size(); ++i) {
        if (vouchers[i]->toString() == code) {
            vouchers.erase(vouchers.begin() + i);
            break;
        }
    }
}