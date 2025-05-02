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

// Service class for customer-related business logic
class CustomerService {
public:
    // Search music catalog by criteria (name/artist/genre) and keyword
    // Returns a vector of matching music items
    static vector<Music> searchMusic(const vector<Music>& items, const string& criteria, const string& keyword);
    
    // Add a music item to the shopping cart
    // Returns true if successful, false if invalid ID or insufficient stock
    static bool addItemToCart(Cart& cart, vector<Music>& inventory, int itemID, int quantity);
    
    // Remove an item from the shopping cart
    // Returns true if successful, false if invalid item ID
    static bool removeItemFromCart(Cart& cart, vector<Music>& inventory, int itemID);
    
    // Process order checkout and create a new order
    static void checkout(vector<Order>& orders, const string& username, Cart& cart, float total);
    
    // Retrieve orders for a specific user
    // Returns a vector of orders made by the specified user
    static vector<Order> getUserOrders(const vector<Order>& orders, const string& username);
    
    // Create a new discount voucher for a user
    static void createNewVoucher(vector<shared_ptr<IDiscount>>& vouchers, 
                                const string& username, int discountType, int discountValue);
};

#endif