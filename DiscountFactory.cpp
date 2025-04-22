#include "DiscountFactory.h"
#include "Database.h"
#include <algorithm>
#include <regex> // For extracting numbers from voucher codes

DiscountFactory* DiscountFactory::getInstance() {
    if (!instance) {
        instance = new DiscountFactory();
    }
    return instance;
}

DiscountFactory::DiscountFactory() {
    classifyVouchers();
}

void DiscountFactory::classifyVouchers() {
    vector<string> vouchers;
    Database::getInstance()->loadVoucher(vouchers);

    for (const auto& voucher : vouchers) {
        // Extract the discount value using regex
        std::regex regex("(\\d+)");
        std::smatch match;
        if (std::regex_search(voucher, match, regex)) {
            int discountValue = std::stoi(match.str()); // Extracted discount value

            if (voucher.find("P") != string::npos) { // Percentage discount
                vector<string> codes = {voucher};
                discounts.push_back(make_shared<PercentageDiscount>(discountValue, codes));
            } else if (voucher.find("F") != string::npos) { // Fixed amount discount
                vector<string> codes = {voucher};
                discounts.push_back(make_shared<FixedAmountDiscount>(discountValue, codes));
            }
        }
    }
}

float DiscountFactory::applyDiscount(const string& code, const float& total) {
    for (const auto& discount : discounts) {
        if (discount->isValidCode(code)) {
            float newTotal = discount->applyDiscount(total);

            // Remove the voucher from the list after applying it
            vector<string> vouchers;
            Database::getInstance()->loadVoucher(vouchers);
            auto it = std::find(vouchers.begin(), vouchers.end(), code);
            if (it != vouchers.end()) {
                vouchers.erase(it);
                Database::getInstance()->saveVoucher(vouchers);
            }

            return newTotal;
        }
    }

    return -1; // Invalid code, return -1 to indicate no discount applied
}