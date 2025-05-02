#ifndef _CUSTOMER_SERVICE_H_
#define _CUSTOMER_SERVICE_H_

#include "Music.h"
#include "Cart.h"
#include "Order.h"
#include "Discount.h"
#include <vector>
#include <memory>
#include <string>

using std::vector, std::shared_ptr, std::string;

/**
 * @brief Service class for customer-related business logic
 */
class CustomerService {
public:
    /**
     * @brief Search music catalog by criteria (name/artist/genre) and keyword
     * 
     * @param items Vector of music items to search through
     * @param criteria Search criteria (name, artist, or genre)
     * @param keyword Keyword to search for
     * @return vector<Music> Vector of music items matching the search criteria
     * @throws std::invalid_argument If an invalid search criteria is provided
     */
    static vector<Music> searchMusic(const vector<Music>& items, const string& criteria, const string& keyword);
    
    /**
     * @brief Add a music item to the shopping cart
     * 
     * @param cart Reference to the customer's shopping cart
     * @param inventory Reference to the store's music inventory
     * @param itemID Index of the item to add
     * @param quantity Quantity of the item to add
     * @return bool True if successful, false if invalid ID or insufficient stock
     */
    static bool addItemToCart(Cart& cart, vector<Music>& inventory, int itemID, int quantity);
    
    /**
     * @brief Remove an item from the shopping cart
     * 
     * @param cart Reference to the customer's shopping cart
     * @param inventory Reference to the store's music inventory
     * @param itemID Index of the item to remove from cart
     * @return bool True if successful, false if invalid item ID
     */
    static bool removeItemFromCart(Cart& cart, vector<Music>& inventory, int itemID);
    
    /**
     * @brief Process order checkout and create a new order
     * 
     * @param orders Reference to the system's order history
     * @param username Username of the customer checking out
     * @param cart Reference to the customer's shopping cart
     * @param total Total price of the order after any discounts
     */
    static void checkout(vector<Order>& orders, const string& username, Cart& cart, float total);
    
    /**
     * @brief Retrieve orders for a specific user
     * 
     * @param orders Vector of all orders in the system
     * @param username Username to filter orders by
     * @return vector<Order> Vector of orders made by the specified user
     */
    static vector<Order> getUserOrders(const vector<Order>& orders, const string& username);
    
    /**
     * @brief Create a new discount voucher for a user
     * 
     * @param vouchers Reference to the system's discount vouchers
     * @param username Username of the customer to create voucher for
     * @param discountType Type of discount (1 for percentage, 2 for fixed)
     * @param discountValue Value of the discount (percentage or amount)
     */
    static void createNewVoucher(vector<shared_ptr<IDiscount>>& vouchers, 
                                const string& username, int discountType, int discountValue);
};

#endif