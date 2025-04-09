#ifndef _CUSTOMER_MENU_H_
#define _CUSTOMER_MENU_H_

#include "InventoryManager.h"
#include "Cart.h"
#include "Order.h"
#include "UI.h"


class CustomerMenu {
public:
    static void run(InventoryManager&, Cart&, Customer&);
};


#endif