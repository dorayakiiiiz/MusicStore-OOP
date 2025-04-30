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

class StoreApp {
private:
    vector<Music> items;
    vector<shared_ptr<IUser>> users;
    vector<Order> orders;
    vector<shared_ptr<IDiscount>> vouchers;
public:
    StoreApp();
    ~StoreApp();
    void run();
};

#endif