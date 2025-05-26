/**
 * @file CustomerUI.h
 * @brief Header file for the CustomerUI class
 * 
 * @details Defines the CustomerUI class which provides display functions
 *          and input collection methods for the customer interface
 */

#ifndef _CUSTOMER_UI_H_
#define _CUSTOMER_UI_H_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Order.h"
#include "Music.h"
#include "Discount.h"
#include <tuple>
#include "utils.h"

using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple;
using std::shared_ptr, std::make_shared;

/**
 * @brief UI class for customer interface
 * 
 * @details Provides methods for displaying customer-specific UI elements
 */
class CustomerUI {
public:
    /**
     * @brief Displays a welcome message for the customer
     * @param username The username of the customer
     */
    static void displayWelcomeMessage(const string& username);

    /**
     * @brief Displays the order history for a specific customer
     * @param orders Vector of orders to display
     * @param username Username to filter orders by
     */
    static void displayPurchasedHistory(const vector<Order>& orders);
    
    /**
     * @brief Displays a formatted list of all music items
     * @param items Vector containing all music items to display
     */
    static void displayMusicList(vector<Music>& items, int maxPerPage);

    /**
     * @brief Displays the current items in the shopping cart
     * @param items Vector of items in the cart
     */
    static void displayCart(const vector<Music>& items, int maxPerPage);
    
    /**
     * @brief Displays a message when no search results are found
     */
    static void displayNoResultsMessage();

    /**
     * @brief Displays search results from a music search operation
     * @param results Vector of music items matching the search criteria
     */
    static void displaySearchResults(vector<Music>& results);

    /**
     * @brief Displays a message when attempting to checkout with an empty cart
     */
    static void displayEmptyCartMessage();
    
    /**
     * @brief Displays order details before confirming checkout
     * @param username Username of the customer placing the order
     * @param items Vector of items being purchased
     * @param total Total price of the order
     */
    static void displayOrderDetails(const string& username, const vector<Music>& items, float total);
    
    /**
     * @brief Displays the list of available discount vouchers for the customer
     * @param vouchers Vector of discount vouchers available to the customer
     */
    static void displayVoucherList(const vector<shared_ptr<Discount>>& vouchers);

    /**
     * @brief Displays discount options after a large purchase (over $50)
     */
    static void displayDiscountOptions();

    /**
     * @brief Displays a success message after completing an order
     */
    static void displayOrderSuccessMessage();
    
    /**
     * @brief Displays a message when the customer logs out
     */
    static void displayLogoutMessage();
    
    /**
     * @brief Displays a warning when attempting to log out with items still in cart
     */
    static void displayCartWarningMessage();
    
    /**
     * @brief Displays a message for invalid menu choices
     */
    static void displayInvalidChoiceMessage();
};

#endif