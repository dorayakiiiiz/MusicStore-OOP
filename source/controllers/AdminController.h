/**
 * @file AdminController.h
 * @brief Header file for the AdminController class
 * 
 * @details Defines the AdminController class which is responsible for all administrative
 * operations in the music store system including inventory management, user management,
 * and sales reporting.
 */

#ifndef _ADMIN_CONTROLLER_H_
#define _ADMIN_CONTROLLER_H_

/**
 * @brief Enumeration for admin menu options
 */
enum AdminOption {
    ADMIN_MUSIC_LIST = 1,
    ADD_NEW_ITEMS = 2,
    REMOVE_ITEMS = 3,
    UPDATE_PRICE = 4,
    VIEW_USERS = 5,
    VIEW_PURCHASE_HISTORY = 6,
    DELETE_CUSTOMERS = 7,
    VIEW_SALES_STATISTICS = 8,
    ADMIN_LOGOUT = 9
};

#include "IController.h"

/**
 * @brief Controller class for administrator-specific functionality
 * 
 * @details Handles all administrative operations including inventory management, user management, and sales reporting
 */
class AdminController : public IController {
public:
    /**
     * @brief Constructor for AdminController
     */
    AdminController();
    
    /**
     * @brief Implements the admin menu interface and all administrative operations
     * 
     * @param currentUser Reference to the currently logged-in admin user
     */
    void menu(shared_ptr<User>& currentUser) override;
};

#endif