#ifndef _CUSTOMER_CONTROLLER_H_
#define _CUSTOMER_CONTROLLER_H_

#include "InventoryManager.h"
#include "Cart.h"
#include "Order.h"
#include "utils.h"


class CustomerController {
public:
    static void run(InventoryManager&, Cart&, Customer&);
};


#endif