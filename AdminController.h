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
private:
    MusicService& musicService; /**< Reference to the music service for inventory operations */
    UserService& userService;   /**< Reference to the user service for user management */
    OrderService& orderService; /**< Reference to the order service for order management */
public:
    /**
     * @brief Constructor for AdminController
     * 
     * @param musicService Reference to the music service for inventory operations
     * @param userService Reference to the user service for user management
     * @param orderService Reference to the order service for order management
     */
    AdminController(MusicService& musicService, UserService& userService, OrderService& orderService);

    /**
     * @brief Implements the admin menu interface and all administrative operations
     * 
     * @param items Reference to the store's music inventory
     * @param users Reference to the system's user accounts
     * @param orders Reference to the system's order history
     * @param vouchers Reference to available discount vouchers
     * @param currentUser Reference to the currently logged-in admin user
     */
    void menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<Discount>>& vouchers, shared_ptr<IUser>& currentUser) override;

    /**
     * @brief Handles displaying the music inventory list
     * 
     * @param items Reference to the store's music inventory
     */
    void handleMusicList(vector<Music>& items);

    /**
     * @brief Handles adding new music items to inventory
     * 
     * @param items Reference to the store's music inventory
     */
    void handleAddNewItems(vector<Music>& items);
    
    /**
     * @brief Handles removing music items from inventory
     * 
     * @param items Reference to the store's music inventory
     */
    void handleRemoveItems(vector<Music>& items);
    
    /**
     * @brief Handles updating price of music items
     * 
     * @param items Reference to the store's music inventory
     */
    void handleUpdatePrice(vector<Music>& items);
    
    /**
     * @brief Handles displaying the list of users
     * 
     * @param users Reference to the system's user accounts
     */
    void handleViewUsers(vector<shared_ptr<IUser>>& users);
    
    /**
     * @brief Handles displaying purchase history for all customers
     * 
     * @param users Reference to the system's user accounts
     * @param orders Reference to the system's order history
     */
    void handleViewPurchaseHistory(vector<shared_ptr<IUser>>& users, vector<Order>& orders);
    
    /**
     * @brief Handles deleting customer accounts
     * 
     * @param users Reference to the system's user accounts
     * @param currentUser Reference to the currently logged-in admin user
     * @return true if admin deleted their own account and needs to logout, false otherwise
     */
    bool handleDeleteCustomers(vector<shared_ptr<IUser>>& users, shared_ptr<IUser>& currentUser);
    
    /**
     * @brief Handles displaying sales statistics
     * 
     * @param orders Reference to the system's order history
     * @param items Reference to the store's music inventory
     */
    void handleViewSalesStatistics(vector<Order>& orders, vector<Music>& items);
    
    /**
     * @brief Handles the admin logout process
     * 
     * @param currentUser Reference to the currently logged-in admin user
     */
    void handleLogout(shared_ptr<IUser>& currentUser);
};

#endif