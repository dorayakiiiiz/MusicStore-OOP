#include "CustomerService.h"
#include "DiscountFactory.h"

#include <stdexcept>

// Direct implementation of search functionality
vector<Music> CustomerService::searchMusic(const vector<Music>& items,const string& criteria, const string& keyword) {
    string kw = keyword;
    for (auto& c : kw) {
        c = tolower(c);
    }
    
    vector<Music> results;
    for (const auto& item : items) {
        string str = (criteria == "name") ? item.getName() : 
                       (criteria == "artist") ? item.getArtist() : 
                       (criteria == "genre") ? item.getGenre() : 
                       throw std::invalid_argument("Invalid search criteria!");       
        for (auto& c : str) {
            c = tolower(c);
        }
        
        if (str.find(kw) != string::npos) {
            results.push_back(item);
        }
    }
    
    return results;
}

// Direct implementation of cart operations
bool CustomerService::addItemToCart(Cart& cart, vector<Music>& inventory, int itemID, int quantity) {
    if (itemID < 0 || itemID >= inventory.size()) {
        return false;
    }
    
    if (quantity <= 0 || inventory[itemID].getQuantity() < quantity) {
        return false;
    }
    
    Music item = inventory[itemID];
    item.updateQuantity(quantity);
    cart.addItems(item, quantity);
    inventory[itemID].updateQuantity(inventory[itemID].getQuantity() - quantity);
    
    return true;
}

bool CustomerService::removeItemFromCart(Cart& cart, vector<Music>& inventory, int itemID) {
    if (itemID < 0 || itemID >= cart.getItems().size()) {
        return false;
    }
    
    // Add item quantity back to inventory
    for (auto& item : inventory) {
        if (item == cart.getItems()[itemID]) {
            item.updateQuantity(item.getQuantity() + cart.getItems()[itemID].getQuantity());
            break;
        }
    }
    
    cart.removeItem(itemID);
    return true;
}

// Checkout implementation
void CustomerService::checkout(vector<Order>& orders, const string& username, Cart& cart, float total) {
    Order order(username, cart.getItems(), total);
    orders.push_back(order);
    cart.clear();
}

// Get user orders
vector<Order> CustomerService::getUserOrders(const vector<Order>& orders, const string& username) {
    vector<Order> userOrders;
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}


// Create new voucher implementation 
void CustomerService::createNewVoucher(vector<shared_ptr<IDiscount>>& vouchers, 
                                  const string& username, int discountType, int discountValue) {
    if (discountType == 1) {
        vouchers.push_back(make_shared<PercentageDiscount>(username, discountValue));
    } else {
        vouchers.push_back(make_shared<FixedDiscount>(username, discountValue));
    }
}