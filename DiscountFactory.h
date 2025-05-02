#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "Discount.h"
#include <memory>
#include <string>
#include <vector>
using std::shared_ptr, std::make_unique, std::string, std::vector, std::make_shared;

// Factory class for handling discount-related operations
class DiscountFactory {
public:
    // Apply a discount to a total price and return the discounted amount
    static float applyDiscount(shared_ptr<IDiscount>, float);
    
    // Check if a discount exists in the list of vouchers
    static bool isValidDiscount(vector<shared_ptr<IDiscount>>, shared_ptr<IDiscount>);
    
    // Get all valid discounts for a specific username
    static vector<shared_ptr<IDiscount>> loadValidDiscounts(const vector<shared_ptr<IDiscount>>&, const string&);
    
    // Remove a specific discount from the list using its code
    static void removeDiscount(vector<shared_ptr<IDiscount>>&, const string&);
};

#endif