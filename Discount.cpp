#include "Discount.h"

// Get the username associated with this discount
string IDiscount::getUsername() const {
    return username;
}

// Constructor for base discount class
IDiscount::IDiscount(string username) : username(username) {}

// Constructor for percentage discount
PercentageDiscount::PercentageDiscount(string username, int percentage) : IDiscount(username), percentage(percentage) {}

// Convert percentage discount to string representation for storage
string PercentageDiscount::toString() const {
    return username + "P" + std::to_string(percentage);
}

// Constructor for fixed amount discount
FixedDiscount::FixedDiscount(string username, int amount) : IDiscount(username), amount(amount) {}

// Convert fixed discount to string representation for storage
string FixedDiscount::toString() const {
    return username + "F" + std::to_string(amount);
}

// Factory method to create a discount object from string
shared_ptr<IDiscount> IDiscount::toDiscount(const string& str) {
    if (str.find("P") != string::npos) {
        // For percentage discount (e.g., "usernameP10" for 10% discount)
        return make_shared<PercentageDiscount>(str.substr(0, str.find("P")), stoi(str.substr(str.find("P") + 1)));
    } else if (str.find("F") != string::npos) {
        // For fixed discount (e.g., "usernameF5" for $5 discount)
        return make_shared<FixedDiscount>(str.substr(0, str.find("F")), stoi(str.substr(str.find("F") + 1)));
    }
    return nullptr;
}

// Get the type of discount - "percentage"
string PercentageDiscount::getType() const {
    return "percentage";
}

// Get the type of discount - "fixed"
string FixedDiscount::getType() const {
    return "fixed";
}

// Get the percentage value
float PercentageDiscount::getDiscountValue() const {
    return percentage;
}

// Get the fixed amount value
float FixedDiscount::getDiscountValue() const {
    return amount;
}

// Virtual destructor for base discount class
IDiscount::~IDiscount() {}