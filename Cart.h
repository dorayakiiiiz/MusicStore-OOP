#ifndef _CART_H_
#define _CART_H_

#include "MusicItem.h"
#include "Discount.h"
#include <vector>
#include <utility>
#include <memory>
using std::vector, std::pair, std::unique_ptr;

class Cart {
private:
    vector<pair<MusicItem, int>> items;
    unique_ptr<Discount> discount;
public:
    void addItems(const MusicItem&, int);
    void removeItem(int);
    void applyDiscount(unique_ptr<Discount>);
    float calculateTotal() const;
    const vector<pair<MusicItem, int>>& getItems() const;
    void clear();
};


#endif