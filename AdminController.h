#ifndef _ADMIN_CONTROLLER_H_
#define _ADMIN_CONTROLLER_H_

#include "IController.h"
#include "AdminUI.h"

/**
 * @brief Controller class for administrator-specific functionality
 * 
 * @details Handles all administrative operations including inventory management, user management, and sales reporting
 */
class AdminController : public IController {
public:
    /**
     * @brief Implements the admin menu interface and all administrative operations
     * 
     * @param items Reference to the store's music inventory
     * @param users Reference to the system's user accounts
     * @param orders Reference to the system's order history
     * @param vouchers Reference to available discount vouchers
     * @param currentUser Reference to the currently logged-in admin user
     */
    void menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) override;
};

#endif