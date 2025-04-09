#ifndef _CART_H_
#define _CART_H_

#include "MusicItem.h"
#include "Discount.h"
#include <vector>
using std::vector;

class Cart {
private:
    vector<MusicItem> items;
    Discount* discount = nullptr;
public:
    void addItems(const MusicItem&);
    void removeItem(int);
    void applyDiscount(Discount*);
    float calculateTotal() const;
    const vector<MusicItem>& getItems() const;
};


#endif