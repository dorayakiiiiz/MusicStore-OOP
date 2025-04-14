#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "Discount.h"
#include <memory>
#include <string>
using std::string, std::unique_ptr, std::make_unique;
class DiscountFactory {
public:
    static unique_ptr<Discount> createDiscount(const string&, float);
};


#endif