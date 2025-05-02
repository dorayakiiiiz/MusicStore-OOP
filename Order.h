#ifndef _ORDER_H_
#define _ORDER_H_

#include <vector>
#include <string>
#include <utility>
#include "Music.h"
using std::string, std::vector, std::pair;

// Class representing a customer order in the system
class Order {
private:
    string username;             // Username of the customer who placed the order
    vector<Music> purchasedItems; // List of music items in the order
    float total;                 // Total price of the order (after discounts)
public:
    // Constructor - creates a new order with customer username, purchased items and total price
    Order(const string&, const vector<Music>&, const float&);
    
    // Get the total price of the order
    float getTotal() const;
    
    // Get the username of the customer who placed the order
    string getUsername() const;
    
    // Get the list of purchased music items
    const vector<Music>& getPurchasedItems() const;
};

#endif