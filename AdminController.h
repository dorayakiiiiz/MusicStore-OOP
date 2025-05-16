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
#include "AdminUI.h"

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

    /**
     * @brief Handles displaying the music inventory list
     */
    void handleMusicList();

    /**
     * @brief Handles adding new music items to inventory
     */
    void handleAddNewItems();
    
    /**
     * @brief Handles removing music items from inventory
     */
    void handleRemoveItems();
    
    /**
     * @brief Handles updating price of music items
     */
    void handleUpdatePrice();
    
    /**
     * @brief Handles displaying the list of users
     */
    void handleViewUsers();
    
    /**
     * @brief Handles displaying purchase history for all customers
     * 
     * @param users Reference to the system's user accounts
     * @param orders Reference to the system's order history
     */
    void handleViewPurchaseHistory();
    
    /**
     * @brief Handles deleting customer accounts
     * 
     * @param users Reference to the system's user accounts
     * @param currentUser Reference to the currently logged-in admin user
     * @return true if admin deleted their own account and needs to logout, false otherwise
     */
    bool handleDeleteUser(shared_ptr<User>& currentUser);
    
    /**
     * @brief Handles displaying sales statistics
     * 
     * @param orders Reference to the system's order history
     * @param items Reference to the store's music inventory
     */
    void handleViewSalesStatistics();
    
    /**
     * @brief Handles the admin logout process
     * 
     * @param currentUser Reference to the currently logged-in admin user
     */
    void handleLogout(shared_ptr<User>& currentUser);
};

#endif