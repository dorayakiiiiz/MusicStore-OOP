#ifndef _STORE_APP_H_
#define _STORE_APP_H_

#include "Music.h"
#include "Order.h"
#include "User.h"
#include "Cart.h"
#include "Discount.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

using std::vector, std::string, std::cout, std::endl, std::make_shared, std::shared_ptr, std::endl, std::map;

// Main application class that manages the entire music store system
class StoreApp {
private:
    vector<Music> items;             // Collection of music items available in the store
    vector<shared_ptr<IUser>> users; // Collection of registered users (customers and admins)
    vector<Order> orders;            // Collection of all placed orders
    vector<shared_ptr<IDiscount>> vouchers; // Collection of available discount vouchers

public:
    // Constructor - loads data from files
    StoreApp();
    
    // Destructor - saves data to files before application exits
    ~StoreApp();
    
    // Main application loop that handles user authentication and navigation
    void run();
};

#endif