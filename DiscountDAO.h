#ifndef _VOUCHER_DAO_H_
#define _VOUCHER_DAO_H_
#include <vector>
#include <string>
#include "Discount.h"
using std::vector, std::string;

class DiscountDAO {
public:
    static void loadDiscount(vector<IDiscount*>&);
    static void saveDiscount(const vector<IDiscount*>&);
};

#endif