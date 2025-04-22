#ifndef _DISCOUNT_H_
#define _DISCOUNT_H_

#include <string>
#include <vector>
using std::string, std::vector;

class IDiscount {
public:
    virtual float applyDiscount(const float& price) const = 0;
    virtual bool isValidCode(const string& code) const = 0;
    virtual ~IDiscount() = default;
};

class PercentageDiscount : public IDiscount {
private:
    float percentage;
    vector<string> codes; 
public:
    PercentageDiscount(float percentage, const vector<string>& codes);
    float applyDiscount(const float& price) const override;
    bool isValidCode(const string& code) const override;
};

class FixedAmountDiscount : public IDiscount {
private:
    float amount;
    vector<string> codes; 
public:
    FixedAmountDiscount(float amount, const vector<string>& codes);
    float applyDiscount(const float& price) const override;
    bool isValidCode(const string& code) const override;
};

#endif