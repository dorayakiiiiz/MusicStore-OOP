/**
 * @file CustomerController.h
 * @brief Header file for the CustomerController class
 * 
 * @details Defines the CustomerController class which handles customer operations
 *          including viewing music, searching, cart management, and checkout
 */

#ifndef _CUSTOMER_CONTROLLER_H_
#define _CUSTOMER_CONTROLLER_H_

#include "IController.h"

/**
 * @brief Enumeration for customer menu options
 */
enum CustomerOption {
    PURCHASE_HISTORY = 1,
    CUSTOMER_MUSIC_LIST = 2,
    SEARCH_ENGINE = 3,
    ADD_TO_CART = 4,
    REMOVE_FROM_CART = 5,
    CHECKOUT = 6,
    CUSTOMER_LOGOUT = 7
};

enum Agreement {
    YES = 1,
    NO = 2
};


/**
 * @brief Controller class for customer-specific functionality
 * 
 * @details Handles all customer operations including browsing music, managing cart, and placing orders
 */
class CustomerController : public IController {
public:
    /**
     * @brief Constructor for CustomerController
     */
    CustomerController();
    
    /**
     * @brief Implements the customer menu interface and all customer operations
     * 
     * @param currentUser Reference to the currently logged-in user
     */
    void menu(shared_ptr<User>& currentUser) override;


    /**
     * @brief Handles the purchase history display for the customer
     * 
     * @param currentUser Reference to the currently logged-in user
     */
    void handlePurchaseHistory(Customer*& customer);


    /**
     * @brief Handles the music list display for the customer
     * 
     * @param items Reference to the store's music inventory
     */
    void handleMusicList();

    /**
     * @brief Handles the search engine functionality for the customer
     * 
     * @param items Reference to the store's music inventory
     */
    void handleSearch();

    /**
     * @brief Handles adding items to the customer's shopping cart
     * 
     * @param items Reference to the store's music inventory
     * @param cart Reference to the customer's shopping cart
     */
    void handleAddToCart(Cart& cart);

    /**
     * @brief Handles removing items from the customer's shopping cart
     * 
     * @param cart Reference to the customer's shopping cart
     */
    void handleRemoveFromCart(Cart& cart);

    /**
     * @brief Handles the checkout process for the customer
     * 
     * @param cart Reference to the customer's shopping cart
     * @param customer Reference to the currently logged-in customer
     */
    void handleCheckout(Cart& cart, Customer*& customer);

    /**
     * @brief Handle the log out process of the customer
     * 
     * @param cart Reference to the customer's shopping cart
     * @param customer Reference to the currently logged-in customer
     * 
     * @return true if the cart is checked out
     */
    bool handleLogout(Cart& cart, shared_ptr<User>& currentUser);
};

#endif

