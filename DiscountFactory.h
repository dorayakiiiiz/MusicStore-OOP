#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "Discount.h"
#include <memory>
#include <string>
#include <vector>
using std::shared_ptr, std::make_unique, std::string, std::vector, std::make_shared;

class DiscountFactory {
private:
    inline static DiscountFactory* instance = nullptr;
    vector<shared_ptr<IDiscount>> discounts;

    void classifyVouchers();
public:
    static DiscountFactory* getInstance();
    DiscountFactory();
    float applyDiscount(const string& code, const float& total);
};

#endif