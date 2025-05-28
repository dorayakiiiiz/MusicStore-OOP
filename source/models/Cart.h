/**
 * @file Cart.h
 * @brief Header file for the Cart class
 * 
 * @details Defines the Cart class which manages a customer's shopping cart
 *          during a shopping session
 */

#ifndef _CART_H_
#define _CART_H_

#include "Music.h"
#include "Discount.h"
#include <vector>
#include <memory>
using std::vector, std::pair, std::unique_ptr;

/**
 * @brief Class representing a customer's shopping cart
 */
class Cart {
private:
    vector<Music> _items; /**< List of music items in the cart */
public:
    /**
     * @brief Add a music item to the cart with specified quantity
     * 
     * @param item The music item to add
     * @param quantity The quantity of the item to add
     */
    void addItems(Music, int);
    
    /**
     * @brief Remove an item from the cart by index
     * 
     * @param id The index of the item to remove
     */
    void removeItem(int);
    
    /**
     * @brief Calculate the total price of all items in the cart
     * 
     * @return float The total price of all items
     */
    float calculateTotal() const;
    
    /**
     * @brief Get the list of music items in the cart
     * 
     * @return const vector<Music>& Reference to the vector of items in the cart
     */
    const vector<Music>& getItems() const;
    
    /**
     * @brief Clear all items from the cart
     */
    void clear();
};

#endif