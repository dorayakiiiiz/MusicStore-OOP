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
 * @brief Controller class for customer-specific functionality
 * 
 * @details Handles all customer operations including browsing music, managing cart, and placing orders
 */
class CustomerController : public IController {
private:
    MusicService& musicService;
    CartService& cartService;
    OrderService& orderService;
    DiscountService& discountService;
public:
    /**
     * @brief Constructor for CustomerController
     * 
     * @param musicService Reference to the music service for inventory operations
     * @param cartService Reference to the cart service for shopping cart operations
     * @param orderService Reference to the order service for order management
     * @param discountService Reference to the discount service for managing discounts
     */
    CustomerController(MusicService& musicService, CartService& cartService, OrderService& orderService, DiscountService& discountService);
    
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


    /**
     * @brief Handles the purchase history display for the customer
     * 
     * @param orders Reference to the system's order history
     * @param currentUser Reference to the currently logged-in user
     */
    void handlePurchaseHistory(vector<Order>& orders, Customer*& customer);


    /**
     * @brief Handles the music search functionality for the customer
     * 
     * @param items Reference to the store's music inventory
     * @param currentUser Reference to the currently logged-in user
     */
    void handleMusicList(vector<Music>& items);

    /**
     * @brief Handles the cart operations for the customer
     * 
     * @param items Reference to the store's music inventory
     * @param currentUser Reference to the currently logged-in user
     */
    void handleSearch(vector<Music>& items);

    /**
     * @brief Handles the checkout process for the customer
     * 
     * @param orders Reference to the system's order history
     * @param currentUser Reference to the currently logged-in user
     * @param cart Reference to the customer's shopping cart
     */
    void handleAddToCart(vector<Music>& item, Cart& cart);

    /**
     * @brief Handles the checkout process for the customer
     * 
     * @param orders Reference to the system's order history
     * @param currentUser Reference to the currently logged-in user
     * @param cart Reference to the customer's shopping cart
     */
    void handleRemoveFromCart(Cart& cart, vector<Music>& items);

    /**
     * @brief Handles the checkout process for the customer
     * 
     * @param orders Reference to the system's order history
     * @param items Reference to the store's music inventory
     * @param cart Reference to the customer's shopping cart
     * @param vouchers Reference to available discount vouchers
     * @param currentUser Reference to the currently logged-in user
     */
    void handleCheckout(vector<Order>& orders, vector<Music>& items, Cart& cart, vector<shared_ptr<Discount>>& vouchers, Customer*& customer);

    /**
     * @brief Handles the logout process for the customer
     * 
     * @param cart Reference to the customer's shopping cart
     * @param currentUser Reference to the currently logged-in user
     * @return true if logout was successful, false otherwise
     */
    bool handleLogout(Cart& cart, shared_ptr<IUser>& currentUser);
};

#endif

