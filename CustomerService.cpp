#include "CustomerService.h"
#include "DiscountFactory.h"

#include <stdexcept>

// Search music catalog by criteria and keyword
vector<Music> CustomerService::searchMusic(const vector<Music>& items,const string& criteria, const string& keyword) {
    // Convert keyword to lowercase for case-insensitive search
    string kw = keyword;
    for (auto& c : kw) {
        c = tolower(c);
    }
    
    vector<Music> results;
    for (const auto& item : items) {
        // Get the appropriate field based on search criteria
        string str = (criteria == "name") ? item.getName() : 
                       (criteria == "artist") ? item.getArtist() : 
                       (criteria == "genre") ? item.getGenre() : 
                       throw std::invalid_argument("Invalid search criteria!");       
        
        // Convert to lowercase for case-insensitive comparison
        for (auto& c : str) {
            c = tolower(c);
        }
        
        // Add item to results if keyword is found
        if (str.find(kw) != string::npos) {
            results.push_back(item);
        }
    }
    
    return results;
}

// Add a music item to the shopping cart
bool CustomerService::addItemToCart(Cart& cart, vector<Music>& inventory, int itemID, int quantity) {
    // Validate itemID
    if (itemID < 0 || itemID >= inventory.size()) {
        return false;
    }
    
    // Validate quantity
    if (quantity <= 0 || inventory[itemID].getQuantity() < quantity) {
        return false;
    }
    
    // Create a copy of the item with the requested quantity
    Music item = inventory[itemID];
    item.updateQuantity(quantity);
    
    // Add to cart and reduce inventory
    cart.addItems(item, quantity);
    inventory[itemID].updateQuantity(inventory[itemID].getQuantity() - quantity);
    
    return true;
}

// Remove an item from the shopping cart
bool CustomerService::removeItemFromCart(Cart& cart, vector<Music>& inventory, int itemID) {
    // Validate itemID
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
    
    // Remove the item from cart
    cart.removeItem(itemID);
    return true;
}

// Process order checkout and create a new order
void CustomerService::checkout(vector<Order>& orders, const string& username, Cart& cart, float total) {
    // Create a new order with current cart items and total
    Order order(username, cart.getItems(), total);
    // Add to orders collection
    orders.push_back(order);
    // Clear the cart after successful checkout
    cart.clear();
}

// Retrieve orders for a specific user
vector<Order> CustomerService::getUserOrders(const vector<Order>& orders, const string& username) {
    vector<Order> userOrders;
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}

// Create a new discount voucher for a user
void CustomerService::createNewVoucher(vector<shared_ptr<IDiscount>>& vouchers, 
                                  const string& username, int discountType, int discountValue) {
    // Create percentage or fixed discount based on type
    if (discountType == 1) {
        vouchers.push_back(make_shared<PercentageDiscount>(username, discountValue));
    } else {
        vouchers.push_back(make_shared<FixedDiscount>(username, discountValue));
    }
}