#ifndef _ORDER_SERVICE_H_
#define _ORDER_SERVICE_H_

#include "Order.h"
#include "Cart.h"
#include <vector>
#include <string>

using std::vector, std::string;

/**
 * @brief Service class for managing order-related operations
 * 
 * @details Provides methods to create new orders and retrieve order history for users
 */
class OrderService {
public:
    /**
     * @brief Default constructor
     */
    OrderService() = default;

    /**
     * @brief Default destructor
     */
    ~OrderService() = default;

    /**
     * @brief Create a new order and add it to the order history
     * 
     * @param orders Vector of all orders in the system
     * @param username Username of the customer placing the order
     * @param cart Reference to the customer's shopping cart
     * @param total Total price of the order after any discounts
     */
    void checkout(const string& username, Cart& cart, float total);
        
    /**
     * @brief Retrieve orders for a specific user
     * 
     * @param orders Vector of all orders in the system
     * @param username Username to filter orders by
     * @return vector<Order> Vector of orders made by the specified user
     */
    vector<Order> getUserOrders(const vector<Order>& orders, const string& username);

    /**
     * @brief Generate sales statistics for all music items
     * 
     * @param orders Vector of all orders to analyze
     * @param items Vector of all music items in inventory
     * @return vector<pair<string, pair<int, float>>> Vector of pairs mapping item names to their sales stats (quantity sold, revenue)
     */
    vector<pair<string, pair<int, float>>> generateSalesStatistics(
        const vector<Order>& orders, const vector<Music>& items);

    /**
     * @brief Get purchase history for a specific user
     * 
     * @param orders Vector of all orders to search in
     * @param username Username to get history for
     * @return vector<Order> Vector of orders made by the specified user
     */
    vector<Order> getUserPurchaseHistory(const vector<Order>& orders, const string& username);
    
};

#endif