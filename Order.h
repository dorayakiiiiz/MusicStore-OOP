#ifndef _ORDER_H_
#define _ORDER_H_

#include <vector>
#include <string>
#include <utility>
#include "MusicItem.h"
using std::string, std::vector, std::pair;

class Order {
private:
    string username;
    vector<MusicItem> purchasedItems;
    float total;
public:
    Order(const string&, const vector<MusicItem>&, const float&);
    float getTotal() const;
    string getUsername() const;
    const vector<MusicItem>& getPurchasedItems() const;
};



#endif