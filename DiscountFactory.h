#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "Discount.h"
#include <memory>
#include <string>
#include <vector>
using std::shared_ptr, std::make_unique, std::string, std::vector, std::make_shared;

class DiscountFactory {
public:
    static float applyDiscount(IDiscount*, float);
    static bool isValidDiscount(vector<IDiscount*> vouchers, IDiscount*);
};

#endif