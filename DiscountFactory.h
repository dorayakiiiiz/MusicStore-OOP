#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "Discount.h"
#include <memory>
#include <string>
#include <vector>
using std::shared_ptr, std::make_unique, std::string, std::vector, std::make_shared;

/**
 * @brief Factory class for handling discount-related operations
 */
class DiscountFactory {
public:
    /**
     * @brief Apply a discount to a total price and return the discounted amount
     * 
     * @param voucher The discount voucher to apply
     * @param total The original total price
     * @return float The discounted price after applying the voucher
     */
    static float applyDiscount(shared_ptr<IDiscount>, float);
    
    /**
     * @brief Check if a discount exists in the list of vouchers
     * 
     * @param vouchers Vector of existing discount vouchers
     * @param voucher The discount voucher to check
     * @return bool True if the voucher exists in the list, false otherwise
     */
    static bool isValidDiscount(vector<shared_ptr<IDiscount>>, shared_ptr<IDiscount>);
    
    /**
     * @brief Get all valid discounts for a specific username
     * 
     * @param vouchers Vector of all available discount vouchers
     * @param username Username to filter vouchers by
     * @return vector<shared_ptr<IDiscount>> Vector of discount vouchers valid for the specified user
     */
    static vector<shared_ptr<IDiscount>> loadValidDiscounts(const vector<shared_ptr<IDiscount>>&, const string&);
    
    /**
     * @brief Remove a specific discount from the list using its code
     * 
     * @param vouchers Vector of discount vouchers to modify
     * @param code The voucher code to remove
     */
    static void removeDiscount(vector<shared_ptr<IDiscount>>&, const string&);
};

#endif