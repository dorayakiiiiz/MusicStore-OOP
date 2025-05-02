#ifndef _DISCOUNT_H_
#define _DISCOUNT_H_

#include <string>
#include <vector>
#include <memory>
using std::string, std::vector, std::shared_ptr, std::make_shared, std::make_unique;

// Abstract base class for all discount types
class IDiscount {
protected:
    string username; // Username of the customer who owns the discount
public:
    // Get the username associated with this discount
    string getUsername() const;
    
    // Constructor with username
    IDiscount(string);
    
    // Convert discount to string representation (for storage)
    virtual string toString() const = 0;
    
    // Get the type of discount ("percentage" or "fixed")
    virtual string getType() const = 0;
    
    // Get the discount value (percentage or amount)
    virtual float getDiscountValue() const = 0;
    
    // Factory method to create a discount object from string
    static shared_ptr<IDiscount> toDiscount(const string&);
    
    // Virtual destructor for proper inheritance
    virtual ~IDiscount();
};

// Percentage discount - reduces total by a percentage
class PercentageDiscount : public IDiscount {
private:
    int percentage; // Percentage value for the discount
public:
    // Constructor with username and percentage value
    PercentageDiscount(string, int);
    
    // Convert to string representation (for storage)
    string toString() const override;
    
    // Get type of discount - returns "percentage"
    string getType() const override;
    
    // Get the percentage value
    float getDiscountValue() const override;
};

// Fixed amount discount - reduces total by a fixed amount
class FixedDiscount : public IDiscount {
private:
    int amount; // Fixed amount to reduce from total
public:
    // Constructor with username and fixed amount
    FixedDiscount(string, int);
    
    // Convert to string representation (for storage)
    string toString() const override;
    
    // Get type of discount - returns "fixed"
    string getType() const override;
    
    // Get the fixed amount value
    float getDiscountValue() const override;
};

#endif