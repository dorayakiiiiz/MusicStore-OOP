#ifndef _CART_SERVICE_H_
#define _CART_SERVICE_H_

#include "Cart.h"
#include "Music.h"

#include <vector>
#include <string>

using std::vector, std::string;

/**
 * @brief Service class for managing shopping cart operations
 * 
 * @details Provides methods to add, remove items from the cart and process orders
 */

class CartService {
public:
    /**
     * @brief Default constructor
     */
    CartService() = default;

    /**
     * @brief Default destructor
     */
    ~CartService() = default;

    /**
     * @brief Add a music item to the shopping cart
     * 
     * @param cart Reference to the customer's shopping cart

     * @param itemID Index of the item to add
     * @param quantity Quantity of the item to add
     * @return bool True if successful, false if invalid ID or insufficient stock
     */
    bool addItemToCart(Cart& cart, int itemID, int quantity);
    
    /**
     * @brief Remove an item from the shopping cart
     * 
     * @param cart Reference to the customer's shopping cart
     * @param inventory Reference to the store's music inventory
     * @return bool True if successful, false if invalid item ID
     */
    bool removeItemFromCart(Cart& cart, int itemID);
    
    /**
     * @brief Process order checkout and create a new order
     * 
     * @param orders Reference to the system's order history
     * @param username Username of the customer checking out
     * @param cart Reference to the customer's shopping cart
     * @param total Total price of the order after any discounts
     */
};

#endif