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
    AuthService auth;   /**< Authentication service for user management */
    shared_ptr<MusicService> musicService;  /**< Music service for inventory operations */
    shared_ptr<UserService> userService;     /**< User service for user management */
    shared_ptr<OrderService> orderService;  /**< Order service for order processing */
    shared_ptr<CartService> cartService;    /**< Cart service for shopping operations */
    shared_ptr<DiscountService> discountService;     /**< Discount service for managing vouchers */
    ControllerFactory controllerFactory;    /**< Factory for creating controllers based on user role */

    /**
     * @brief Initializes all services used in the application
     */
    void initServices();

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
     * @brief Constructor - initializes the StoreApp 
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