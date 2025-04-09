#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "Discount.h"
#include <string>
using std::string;
class DiscountFactory {
public:
    static Discount* createDiscount(const string&, float);
};


#endif