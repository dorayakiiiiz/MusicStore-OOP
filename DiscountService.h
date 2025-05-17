/**
 * @file DiscountService.h
 * @brief Header file for the DiscountService class
 * 
 * @details Defines the DiscountService class which manages discount vouchers
 *          for the music store system
 */

#ifndef _DISCOUNT_SERVICE_H_
#define _DISCOUNT_SERVICE_H_

/**
 * @brief Enumeration for discount types
 */
enum DiscountType {
    PERCENTAGE = 1,
    FIXED_AMOUNT = 2
};


#include "Discount.h"
#include <vector>
#include <memory>
#include <string>
using std::vector, std::shared_ptr, std::string, std::make_shared, std::make_unique;

/**
 * @brief Service class for managing discounts in the system
 */
class DiscountService {
public:
    /**
     * @brief Default constructor
     */
    DiscountService() = default;

    /**
     * @brief Default destructor
     */
    ~DiscountService() = default;

    /**
     * @brief Get all available discount vouchers
     * 
     * @return vector<shared_ptr<Discount>> Vector of all discount vouchers
     */
    vector<shared_ptr<Discount>> getAllDiscounts();
    /**
     * @brief Apply a discount to a total price
     * 
     * @param voucher The discount to apply
     * @param total The original total price
     * @return float The price after applying the discount
     */
    float applyDiscount(const shared_ptr<Discount>& voucher, float total);
    
    /**
     * @brief Check if a discount exists in the list of vouchers
     * 
     * @param vouchers Vector of existing discount vouchers
     * @param voucher The discount voucher to check
     * @return bool True if the voucher exists in the list, false otherwise
     */
    bool isValidDiscount(const vector<shared_ptr<Discount>>& vouchers, 
                               const shared_ptr<Discount>& voucher);
    
    /**
     * @brief Get all valid discounts for a specific username
     * 
     * @param vouchers Vector of all available discount vouchers
     * @param username Username to filter vouchers by
     * @return vector<shared_ptr<Discount>> Vector of discount vouchers valid for the specified user
     */
    vector<shared_ptr<Discount>> loadValidDiscounts(
        const vector<shared_ptr<Discount>>& vouchers, const string& username);
    
    /**
     * @brief Remove a specific discount from the list using its string representation
     * 
     * @param discountString The string representation of the voucher to remove
     */
    void removeDiscount(const string& discountString);
    
    /**
     * @brief Create a new percentage discount
     * 
     * @param username Username associated with the discount
     * @param percentage Percentage value of the discount
     * @return shared_ptr<Discount> New percentage discount
     */
    shared_ptr<Discount> createPercentageDiscount(
        const string& username, int percentage);
    
    /**
     * @brief Create a new fixed amount discount
     * 
     * @param username Username associated with the discount
     * @param amount Fixed amount value of the discount
     * @return shared_ptr<Discount> New fixed amount discount
     */
    shared_ptr<Discount> createFixedDiscount(
        const string& username, float amount);

    /**
     * @brief Create a new discount voucher for a user
     * 
     * @param vouchers Vector of existing discount vouchers
     * @param username Username associated with the discount
     * @param discountType Type of discount (1 for percentage, 2 for fixed)
     * @param discountValue Value of the discount (percentage or amount)
     */
    void createDiscount(const string& username, DiscountType type, int discountValue);
};

#endif