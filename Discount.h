#ifndef _DISCOUNT_H_
#define _DISCOUNT_H_

#include <string>
#include <vector>
#include <memory>
using std::string, std::vector, std::shared_ptr, std::make_shared, std::make_unique;

class IDiscount {
protected:
    string username;
public:
    string getUsername() const;
    IDiscount(string);
    virtual string toString() const = 0;
    virtual string getType() const = 0;
    virtual float getDiscountValue() const = 0;
    static shared_ptr<IDiscount> toDiscount(const string&);
    virtual ~IDiscount();
};

class PercentageDiscount : public IDiscount {
private:
    int percentage;
public:
    PercentageDiscount(string, int);
    string toString() const override;
    string getType() const override;
    float getDiscountValue() const override;
};

class FixedDiscount : public IDiscount {
private:
    int amount;
public:
    FixedDiscount(string, int);
    string toString() const override;
    string getType() const override;
    float getDiscountValue() const override;
};

#endif