/**
 * @file Order.h
 * @brief Header file for the Order class
 * 
 * @details Defines the Order class which represents a completed purchase
 *          transaction in the system
 */

#ifndef _ORDER_H_
#define _ORDER_H_

#include <vector>
#include <string>
#include <utility>
#include "Music.h"
using std::string, std::vector, std::pair;

/**
 * @brief Class representing a customer order in the system
 */
class Order {
private:
    string username;             /**< Username of the customer who placed the order */
    vector<Music> purchasedItems; /**< List of music items in the order */
    float total;                 /**< Total price of the order (after discounts) */
public:

    /**
     * @brief Default constructor - creates an empty order
     */
    Order();

    /**
     * @brief Constructor - creates a new order with customer username, purchased items and total price
     * 
     * @param username Username of the customer who placed the order
     * @param items List of purchased music items
     * @param total Total price of the order
     */
    Order(const string&, const vector<Music>&, const float&);

    /**
     * @brief Copy constructor
     * 
     * @param other Order object to copy from
     */
    Order(const Order& other);
    
    /**
     * @brief Get the total price of the order
     * 
     * @return float The total price of the order
     */
    float getTotal() const;
    
    /**
     * @brief Get the username of the customer who placed the order
     * 
     * @return string Username of the customer
     */
    string getUsername() const;
    
    /**
     * @brief Get the list of purchased music items
     * 
     * @return const vector<Music>& Reference to the vector of purchased items
     */
    const vector<Music>& getPurchasedItems() const;
};

#endif