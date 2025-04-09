#ifndef _ORDER_H_
#define _ORDER_H_

#include <vector>
#include <string>
#include "MusicItem.h"
using std::string, std::vector;

class Order {
private:
    string orderId;
    vector<MusicItem> items;
    float total;
public:
    Order(const vector<MusicItem>&, float);
    string getOrderId() const;
    float getTotal() const;
};



#endif