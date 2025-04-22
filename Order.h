#ifndef _ORDER_H_
#define _ORDER_H_

#include <vector>
#include <string>
#include <utility>
#include "Music.h"
using std::string, std::vector, std::pair;

class Order {
private:
    string username;
    vector<Music> purchasedItems;
    float total;
public:
    Order(const string&, const vector<Music>&, const float&);
    float getTotal() const;
    string getUsername() const;
    const vector<Music>& getPurchasedItems() const;
};



#endif