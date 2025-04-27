#include "DiscountFactory.h"
#include "DiscountDAO.h"
#include <algorithm>

float DiscountFactory::applyDiscount(IDiscount* voucher, float total) {
    string type = voucher->getType();
    if (type == "Percentage") {
        return total - (total * (voucher->getDiscountValue() / 100));
    } else if (type == "Fixed Amount") {
        return total - voucher->getDiscountValue();
    }
    return total;
}

bool DiscountFactory::isValidDiscount(vector<IDiscount*> vouchers, IDiscount* voucher) {
    for (const auto& v : vouchers) {
        if (v->toString() == voucher->toString()) {
            return true;
        }
    }
    return false;
}