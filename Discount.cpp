#include "Discount.h"

string IDiscount::getUsername() const {
    return username;
}

IDiscount::IDiscount(string username) : username(username) {}

PercentageDiscount::PercentageDiscount(string username, int percentage) : IDiscount(username), percentage(percentage) {}

string PercentageDiscount::toString() const {
    return username + "P" + std::to_string(percentage);
}
FixedDiscount::FixedDiscount(string username, int amount) : IDiscount(username), amount(amount) {}

string FixedDiscount::toString() const {
    return username + "F" + std::to_string(amount);
}

shared_ptr<IDiscount> IDiscount::toDiscount(const string& str) {
    if (str.find("P") != string::npos) {
        return make_shared<PercentageDiscount>(str.substr(0, str.find("P")), stoi(str.substr(str.find("P") + 1)));
    } else if (str.find("F") != string::npos) {
        return make_shared<FixedDiscount>(str.substr(0, str.find("F")), stoi(str.substr(str.find("F") + 1)));
    }
    return nullptr;
}

string PercentageDiscount::getType() const {
    return "percentage";
}

string FixedDiscount::getType() const {
    return "fixed";
}

float PercentageDiscount::getDiscountValue() const {
    return percentage;
}

float FixedDiscount::getDiscountValue() const {
    return amount;
}

IDiscount::~IDiscount() {}