#ifndef _DISCOUNT_H_
#define _DISCOUNT_H_

#include <string>
#include <vector>
using std::string, std::vector;

class IDiscount {
public:
    virtual string toString() const = 0;
    virtual string getType() const = 0;
    virtual float getDiscountValue() const = 0;
    static IDiscount* toDiscount(const string&);
};

class PercentageDiscount : public IDiscount {
private:
    string username;
    float percentage;
public:
    PercentageDiscount(string, float);
    string toString() const override;
    string getType() const override;
    float getDiscountValue() const override;
};

class FixedAmountDiscount : public IDiscount {
private:
    string username;
    float amount;
public:
    FixedAmountDiscount(string, float);
    string toString() const override;
    string getType() const override;
    float getDiscountValue() const override;
};

#endif