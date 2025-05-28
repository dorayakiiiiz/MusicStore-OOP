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

using std::string;

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
     * @return string The strategy type name
     */
    virtual string getType() const = 0;
    
    /**
     * @brief Get the value of this discount strategy (percentage or fixed amount)
     * 
     * @return int The discount value
     */
    virtual int getValue() const = 0;

    /**
     * @brief Set the value of this discount strategy (percentage or fixed amount)
     * 
     * @param value The new discount value
     */
    virtual void setValue(int value) = 0; 
    
    /**
     * @brief Create a string representation of the strategy value
     * 
     * @return string String representation of the value
     */
    virtual string toString() const = 0;
};

/**
 * @brief Strategy for percentage-based discounts
 */
class PercentageDiscountStrategy : public DiscountStrategy {
private:
    int _percentage;
    
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
     * @return string The strategy type name
     */
    string getType() const override;
    
    /**
     * @brief Get the value of this discount strategy (percentage or fixed amount)
     * 
     * @return int The discount value
     */
    int getValue() const override;

    /**
     * @brief Set the value of this discount strategy (percentage or fixed amount)
     * 
     * @param value The new discount value
     */ 
    void setValue(int value) override;

    /**
     * @brief Create a string representation of the strategy value
     * 
     * @return string String representation of the value
     */
    
    string toString() const override;
};

/**
 * @brief Strategy for fixed amount discounts
 */
class FixedDiscountStrategy : public DiscountStrategy {
private:
    int _amount;
    
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
     * @return string The strategy type name
     */
    string getType() const override;
    
    /**
     * @brief Get the value of this discount strategy (percentage or fixed amount)
     * 
     * @return float The discount value
     */
    int getValue() const override;

    /**
     * @brief Set the value of this discount strategy (percentage or fixed amount)
     * 
     * @param value The new discount value
     */
    void setValue(int value) override;
    
    /**
     * @brief Create a string representation of the strategy value
     * 
     * @return string String representation of the value
     */
    string toString() const override;
};

#endif