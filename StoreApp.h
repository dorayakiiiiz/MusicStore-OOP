#ifndef _STORE_APP_H_
#define _STORE_APP_H_

#include "Music.h"
#include "Order.h"
#include "User.h"
#include "Cart.h"
#include "Discount.h"
#include "AuthService.h"
#include "MusicService.h"
#include "UserService.h"
#include "OrderService.h"
#include "DiscountService.h"
#include "CartService.h"
#include "ControllerFactory.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

using std::vector, std::string, std::cout, std::endl, std::make_shared, std::shared_ptr, std::endl, std::map;

/**
 * @brief Main application class that manages the entire music store system
 */
class StoreApp {
private:
    // Data
    vector<Music> items; /**< Music inventory */
    vector<shared_ptr<IUser>> users; /**< Registered users */
    vector<Order> orders; /**< Order history */
    vector<shared_ptr<Discount>> vouchers; /**< Discount vouchers */
    
    // Services
    Authentication auth;   /**< Authentication service for user management */
    MusicService musicService;  /**< Music service for inventory operations */
    UserService userService;     /**< User service for user management */
    OrderService orderService;  /**< Order service for order processing */
    CartService cartService;    /**< Cart service for shopping operations */
    DiscountService discountService;     /**< Discount service for managing vouchers */
    ControllerFactory controllerFactory;    /**< Factory for creating controllers based on user role */

    /**
     * @brief Handles the sign up process
     */
    void handleSignUp();

    /**
     * @brief Handles the login process
     * 
     * @param currentUser Reference to store the authenticated user
     * @return true if login was successful, false otherwise
     */
    bool handleLogin(shared_ptr<IUser>& currentUser);

    /**
     * @brief Loads data from files
     */
    void loadData();

    /**
     * @brief Saves data to files
     */
    void saveData();

public:
    /**
     * @brief Constructor - initializes the StoreApp with all required dependencies
     * 
     * @param auth Reference to the Authentication service for user management
     */
    StoreApp();
    
    /**
     * @brief Destructor - saves data to files before application exits
     */
    ~StoreApp();
    
    /**
     * @brief Main application loop that handles user authentication and navigation
     */
    void run();
};

#endif