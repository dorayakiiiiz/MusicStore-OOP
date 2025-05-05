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
    string username;
    unique_ptr<DiscountStrategy> strategy;
    
public:
    /**
     * @brief Constructor for a discount
     * 
     * @param username The username associated with this discount
     * @param strategy The strategy for calculating the discount
     */
    Discount(const string& username, unique_ptr<DiscountStrategy> strategy);
    
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
    
    /**
     * @brief Factory method to create a discount object from string
     * 
     * @param str The string representation of a discount
     * @return shared_ptr<Discount> A new discount object
     */
    static shared_ptr<Discount> fromString(const string& str);
};

#endif