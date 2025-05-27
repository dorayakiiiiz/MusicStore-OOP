#ifndef _ORDER_SERVICE_H_
#define _ORDER_SERVICE_H_

#include "../models/Order.h"
#include "../models/Cart.h"
#include "../database/IDataProvider.h"
#include <vector>
#include <string>
#include <memory>

using std::vector, std::string, std::make_shared, std::shared_ptr;

/**
 * @brief Service class for managing order-related operations
 * 
 * @details Provides methods to create new orders and retrieve order history for users
 */
class OrderService {
private:
    inline static shared_ptr<OrderService> instance = nullptr; /**< Singleton instance of OrderService */

protected:
    OrderService(shared_ptr<IDataProvider> provider); /**< Private constructor for singleton pattern */

    shared_ptr<IDataProvider> dataProvider; /**< Data provider for accessing order data */
public:

    /**
     * @brief Get the singleton instance of OrderService
     * 
     * @param provider Optional data provider to use
     * @return shared_ptr<OrderService> Singleton instance of OrderService
     */
    static shared_ptr<OrderService> getInstance(shared_ptr<IDataProvider> provider = nullptr);

    /**
     * @brief Get all orders in the system
     * 
     * @return vector<Order> Vector of all orders
     */
    vector<Order> getAllOrders();

    /**
     * @brief Delete an order from the system
     * 
     * @param username Username of the customer whose order is to be deleted
     */
    void deleteOrder(const string& username);

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
     * @param username Username to filter orders by
     * @return vector<Order> Vector of orders made by the specified user
     */
    vector<Order> getUserOrders(const string& username);
    
};

#endif