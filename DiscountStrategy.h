/**
 * @file DiscountStrategy.h
 * @brief Header file for discount strategy classes
 * 
 * @details Defines the interface and concrete implementations for
 *          different discount calculation strategies
 */

#ifndef _DISCOUNT_STRATEGY_H_
#define _DISCOUNT_STRATEGY_H_

#include <string>

/**
 * @brief Interface for different discount calculation strategies
 */
class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;
    
    /**
     * @brief Calculate the discount amount based on the total price
     * 
     * @param total The original total price
     * @return float The amount to be discounted
     */
    virtual float calculateDiscount(float total) const = 0;
    
    /**
     * @brief Get the type name of this strategy
     * 
     * @return std::string The strategy type name
     */
    virtual std::string getType() const = 0;
    
    /**
     * @brief Get the value of this discount strategy (percentage or fixed amount)
     * 
     * @return float The discount value
     */
    virtual float getValue() const = 0;
    
    /**
     * @brief Create a string representation of the strategy value
     * 
     * @return std::string String representation of the value
     */
    virtual std::string valueToString() const = 0;
};

/**
 * @brief Strategy for percentage-based discounts
 */
class PercentageDiscountStrategy : public DiscountStrategy {
private:
    int percentage;
    
public:
    /**
     * @brief Construct a new Percentage Discount Strategy
     * 
     * @param percentage The percentage discount value (e.g., 10 for 10%)
     */
    PercentageDiscountStrategy(int percentage);
    
    /**
     * @brief Calculate the discount amount based on the total price
     * 
     * @param total The original total price
     * @return float The amount to be discounted
     */
    float calculateDiscount(float total) const override;

    /**
     * @brief Get the type name of this strategy
     * 
     * @return std::string The strategy type name
     */
    std::string getType() const override;
    
    /**
     * @brief Get the value of this discount strategy (percentage or fixed amount)
     * 
     * @return float The discount value
     */
    float getValue() const override;

    /**
     * @brief Create a string representation of the strategy value
     * 
     * @return std::string String representation of the value
     */
    
    std::string valueToString() const override;
};

/**
 * @brief Strategy for fixed amount discounts
 */
class FixedDiscountStrategy : public DiscountStrategy {
private:
    int amount;
    
public:
    /**
     * @brief Construct a new Fixed Discount Strategy
     * 
     * @param amount The fixed amount to discount
     */
    FixedDiscountStrategy(int amount);
    
    /**
     * @brief Calculate the discount amount based on the total price
     * 
     * @param total The original total price
     * @return float The amount to be discounted
     */
    float calculateDiscount(float total) const override;
    
    /**
     * @brief Get the type name of this strategy
     * 
     * @return std::string The strategy type name
     */
    std::string getType() const override;
    
    /**
     * @brief Get the value of this discount strategy (percentage or fixed amount)
     * 
     * @return float The discount value
     */
    float getValue() const override;
    
    /**
     * @brief Create a string representation of the strategy value
     * 
     * @return std::string String representation of the value
     */
    std::string valueToString() const override;
};

#endif