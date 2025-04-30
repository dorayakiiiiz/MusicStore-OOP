#ifndef _CART_H_
#define _CART_H_

#include "Music.h"
#include "Discount.h"
#include <vector>
#include <memory>
using std::vector, std::pair, std::unique_ptr;

class Cart {
private:
    vector<Music> items;
public:
    void addItems(Music&, int&);
    void removeItem(int);
    void displayCart() const;
    float calculateTotal() const;
    const vector<Music>& getItems() const;
    void clear();
};


#endif