/**
 * @file Discount.h
 * @brief Header file for the Discount class hierarchy
 * 
 * @details Defines the abstract Discount base class and concrete discount types
 *          such as percentage and fixed amount discounts
 */

#ifndef _DISCOUNT_H_
#define _DISCOUNT_H_

#include "DiscountStrategy.h"
#include <memory>
#include <string>

/**
 * @brief Represents a discount that can be applied to a purchase
 */
using std::string, std::unique_ptr, std::shared_ptr;
class Discount {
private:
    string code;
    string username;
    unique_ptr<DiscountStrategy> strategy;
    
public:
    /**
     * @brief Constructor for a discount
     * 
     * @param code The discount code
     * @param username The username associated with this discount
     * @param strategy The strategy for calculating the discount
     */
    Discount(const string& code, const string& username, unique_ptr<DiscountStrategy> strategy);

    /**
     * @brief Get the discount code
     * 
     * @return string The discount code
     */
    string getCode() const;
    
    /**
     * @brief Apply this discount to a total price
     * 
     * @param total The original total price
     * @return float The price after applying the discount
     */
    float apply(float total) const;
    
    /**
     * @brief Get the username associated with this discount
     * 
     * @return string The username
     */
    string getUsername() const;
    
    /**
     * @brief Get the type of discount
     * 
     * @return string The discount type
     */
    string getType() const;
    
    /**
     * @brief Get the value of the discount
     * 
     * @return float The discount value
     */
    float getValue() const;
    
    /**
     * @brief Convert discount to string representation (for storage)
     * 
     * @return string String representation of the discount
     */
    string toString() const;
};

#endif