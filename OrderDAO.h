#ifndef _ORDER_DAO_H_
#define _ORDER_DAO_H_
#include "Order.h"
#include <vector>

class OrderDAO {
public:
    static void saveOrder(const Order&);
    static void loadOrder(vector<Order>&);
};

#endif