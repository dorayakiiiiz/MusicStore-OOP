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

class CustomerService {
public:
    // Search functionality (direct implementation)
    static vector<Music> searchMusic(const vector<Music>& items, const string& criteria, const string& keyword);
    
    // Cart management (direct implementation)
    static bool addItemToCart(Cart& cart, vector<Music>& inventory, int itemID, int quantity);
    static bool removeItemFromCart(Cart& cart, vector<Music>& inventory, int itemID);
    
    // Checkout and order creation
    static void checkout(vector<Order>& orders, const string& username, Cart& cart, float total);
    
    // Order history
    static vector<Order> getUserOrders(const vector<Order>& orders, const string& username);
    
    // Voucher/discount operations
    static void createNewVoucher(vector<shared_ptr<IDiscount>>& vouchers, 
                                const string& username, int discountType, int discountValue);
};

#endif