#ifndef _ORDER_H_
#define _ORDER_H_

#include <vector>
#include <string>
#include <utility>
#include "MusicItem.h"
using std::string, std::vector, std::pair;

class Order {
private:
    string orderId;
    string username;
    vector<pair<int, int>> purchasedItems;
    float total;
public:
    Order(const string&, const string&, const vector<pair<int, int>>&, const float&);
    string getOrderId() const;
    float getTotal() const;
    string getUsername() const;
    const vector<pair<int, int>>& getPurchasedItems() const;
};



#endif