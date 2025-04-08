#ifndef _DISCOUNT_STRATEGY_H_
#define _DISCOUNT_STRATEGY_H_

class Discount {
public:
    virtual float applyDiscount(const float&) = 0;
    virtual ~Discount() = default;
};

class PercentageDiscount : public Discount {
private:
    float percentage;
public:
    PercentageDiscount(const float&);
    float applyDiscount(const float&);
};

class FixedAmountDiscount : public Discount {
private:
    float amount;
public:
    FixedAmountDiscount(const float&);
    float applyDiscount(const float&);
};

#endif