#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "Discount.h"
#include <memory>
#include <string>
#include <vector>
using std::shared_ptr, std::make_unique, std::string, std::vector, std::make_shared;

class DiscountFactory {
public:
    static float applyDiscount(shared_ptr<IDiscount>, float);
    static bool isValidDiscount(vector<shared_ptr<IDiscount>>, shared_ptr<IDiscount>);
    static vector<shared_ptr<IDiscount>> loadValidDiscounts(const vector<shared_ptr<IDiscount>>&, const string&);
    static void removeDiscount(vector<shared_ptr<IDiscount>>&, const string&);
};

#endif