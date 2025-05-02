#ifndef _CART_H_
#define _CART_H_

#include "Music.h"
#include "Discount.h"
#include <vector>
#include <memory>
using std::vector, std::pair, std::unique_ptr;

// Class representing a customer's shopping cart
class Cart {
private:
    vector<Music> items; // List of music items in the cart
public:
    // Add a music item to the cart with specified quantity
    void addItems(Music&, int&);
    
    // Remove an item from the cart by index
    void removeItem(int);
    
    // Display the contents of the cart
    void displayCart() const;
    
    // Calculate the total price of all items in the cart
    float calculateTotal() const;
    
    // Get the list of music items in the cart
    const vector<Music>& getItems() const;
    
    // Clear all items from the cart
    void clear();
};

#endif