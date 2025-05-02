#ifndef _CUSTOMER_CONTROLLER_H_
#define _CUSTOMER_CONTROLLER_H_

#include "IController.h"

// Controller class for customer-specific functionality
class CustomerController : public IController {
public:
    // Implements the customer menu interface and all customer operations
    void menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>&, shared_ptr<IUser>& currentUser) override;
};

#endif

