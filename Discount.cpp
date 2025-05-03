#include "Discount.h"
#include "DiscountStrategy.h"
#include <memory>
#include <stdexcept>

using std::string, std::unique_ptr, std::shared_ptr, std::move, std::exception, std::make_shared, std::make_unique;

// Constructor - creates a discount with a username and strategy
Discount::Discount(const string& username, unique_ptr<DiscountStrategy> strategy)
    : username(username), strategy(move(strategy)) {}

// Apply the discount to a total price
float Discount::apply(float total) const {
    return total - strategy->calculateDiscount(total);
}

// Get the username this discount belongs to
string Discount::getUsername() const {
    return username;
}

// Get the type of discount (Percentage or Fixed Amount)
string Discount::getType() const {
    return strategy->getType();
}

// Get the value of the discount (percentage or amount)
float Discount::getValue() const {
    return strategy->getValue();
}

// Convert the discount to a string format for storage
// Format: usernameXnn where X is type (P/F) and nn is the value
string Discount::toString() const {
    return username + strategy->valueToString();
}

// Create a Discount object from a string representation
// String format should be: usernameXnn (where X is P or F, nn is the value)
shared_ptr<Discount> Discount::fromString(const string& str) {
    if (str.empty()) return nullptr;
    
    // Extract username and discount info
    string username;
    char type = ' ';
    int value = 0;
    
    // Find the type marker (P or F)
    size_t markerPos = string::npos;
    
    if ((markerPos = str.find('P')) != string::npos) {
        type = 'P';  // Percentage discount
    }
    else if ((markerPos = str.find('F')) != string::npos) {
        type = 'F';  // Fixed amount discount
    }
    
    // If no valid marker found, return nullptr
    if (markerPos == string::npos) return nullptr;
    
    // Split the string into username and value parts
    username = str.substr(0, markerPos);
    try {
        // Parse the value part to an integer
        value = stoi(str.substr(markerPos + 1));
    } catch (const exception&) {
        // If conversion fails, return nullptr
        return nullptr;
    }
    
    // Create the appropriate discount type based on the marker
    if (type == 'P') {
        return make_shared<Discount>(username, 
            make_unique<PercentageDiscountStrategy>(value));
    } else {
        return make_shared<Discount>(username, 
            make_unique<FixedDiscountStrategy>(value));
    }
}