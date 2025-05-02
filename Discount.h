#ifndef _DISCOUNT_H_
#define _DISCOUNT_H_

#include <string>
#include <vector>
#include <memory>
using std::string, std::vector, std::shared_ptr, std::make_shared, std::make_unique;

/**
 * @brief Abstract base class for all discount types
 */
class IDiscount {
protected:
    string username; /**< Username of the customer who owns the discount */
public:
    /**
     * @brief Get the username associated with this discount
     * 
     * @return string The username of the customer who owns the discount
     */
    string getUsername() const;
    
    /**
     * @brief Constructor with username
     * 
     * @param username The username of the customer who owns the discount
     */
    IDiscount(string);
    
    /**
     * @brief Convert discount to string representation (for storage)
     * 
     * @return string String representation of the discount
     */
    virtual string toString() const = 0;
    
    /**
     * @brief Get the type of discount ("percentage" or "fixed")
     * 
     * @return string The type of the discount
     */
    virtual string getType() const = 0;
    
    /**
     * @brief Get the discount value (percentage or amount)
     * 
     * @return float The value of the discount
     */
    virtual float getDiscountValue() const = 0;
    
    /**
     * @brief Factory method to create a discount object from string
     * 
     * @param str The string representation of a discount
     * @return shared_ptr<IDiscount> A new discount object based on the string
     */
    static shared_ptr<IDiscount> toDiscount(const string&);
    
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~IDiscount();
};

/**
 * @brief Percentage discount - reduces total by a percentage
 */
class PercentageDiscount : public IDiscount {
private:
    int percentage; /**< Percentage value for the discount */
public:
    /**
     * @brief Constructor with username and percentage value
     * 
     * @param username The username of the customer who owns the discount
     * @param percentage The percentage value for the discount
     */
    PercentageDiscount(string, int);
    
    /**
     * @brief Convert to string representation (for storage)
     * 
     * @return string String representation in format "usernameP{percentage}"
     */
    string toString() const override;
    
    /**
     * @brief Get type of discount - returns "percentage"
     * 
     * @return string The type name "percentage"
     */
    string getType() const override;
    
    /**
     * @brief Get the percentage value
     * 
     * @return float The percentage discount value
     */
    float getDiscountValue() const override;
};

/**
 * @brief Fixed amount discount - reduces total by a fixed amount
 */
class FixedDiscount : public IDiscount {
private:
    int amount; /**< Fixed amount to reduce from total */
public:
    /**
     * @brief Constructor with username and fixed amount
     * 
     * @param username The username of the customer who owns the discount
     * @param amount The fixed amount value for the discount
     */
    FixedDiscount(string, int);
    
    /**
     * @brief Convert to string representation (for storage)
     * 
     * @return string String representation in format "usernameF{amount}"
     */
    string toString() const override;
    
    /**
     * @brief Get type of discount - returns "fixed"
     * 
     * @return string The type name "fixed"
     */
    string getType() const override;
    
    /**
     * @brief Get the fixed amount value
     * 
     * @return float The fixed amount discount value
     */
    float getDiscountValue() const override;
};

#endif