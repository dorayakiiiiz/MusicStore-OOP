#ifndef _CUSTOMER_CONTROLLER_H_
#define _CUSTOMER_CONTROLLER_H_

#include "IController.h"

/**
 * @brief Controller class for customer-specific functionality
 * 
 * @details Handles all customer operations including browsing music, managing cart, and placing orders
 */
class CustomerController : public IController {
public:
    /**
     * @brief Implements the customer menu interface and all customer operations
     * 
     * @param items Reference to the store's music inventory
     * @param users Reference to the system's user accounts
     * @param orders Reference to the system's order history
     * @param discounts Reference to available discount vouchers
     * @param currentUser Reference to the currently logged-in user
     */
    void menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<Discount>>& discounts, shared_ptr<IUser>& currentUser) override;
};

#endif

