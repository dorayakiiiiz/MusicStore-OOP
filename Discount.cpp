#include "Discount.h"

PercentageDiscount::PercentageDiscount(string username, float percentage) : username(username), percentage(percentage) {}

string PercentageDiscount::toString() const {
    // fix to print percentage with 1 decimal place
    string percentageStr = std::to_string(percentage).substr(0, std::to_string(percentage).find(".") + 2);
    return username + "P" + percentageStr;
}
FixedAmountDiscount::FixedAmountDiscount(string username, float amount) : username(username), amount(amount) {}

string FixedAmountDiscount::toString() const {
    string amountStr = std::to_string(amount).substr(0, std::to_string(amount).find(".") + 2);
    return username + "F" + amountStr;
}

IDiscount* IDiscount::toDiscount(const string& str) {
    if (str.find("P") != string::npos) {
        return new PercentageDiscount(str.substr(0, str.find("P")), stof(str.substr(str.find("P") + 1)));
    } else if (str.find("F") != string::npos) {
        return new FixedAmountDiscount(str.substr(0, str.find("F")), stof(str.substr(str.find("F") + 1)));
    }
    return nullptr;
}

string PercentageDiscount::getType() const {
    return "Percentage";
}

string FixedAmountDiscount::getType() const {
    return "Fixed Amount";
}

float PercentageDiscount::getDiscountValue() const {
    return percentage;
}

float FixedAmountDiscount::getDiscountValue() const {
    return amount;
}

