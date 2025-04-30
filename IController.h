#ifndef _ICONTROLLER_H_
#define _ICONTROLLER_H_

#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Cart.h"
#include "Discount.h"
#include "DiscountFactory.h"
#include "ReadData.h"
#include "ReadDataFactory.h"
#include "SaveData.h"
#include "SaveDataFactory.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <algorithm>

using std::vector, std::string, std::cout, std::endl, std::make_shared, std::shared_ptr, std::unordered_map, std::sort, std::pair, std::endl;
using std::shared_ptr, std::make_unique, std::unique_ptr, std::map;
class IController {
public:
    virtual void menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>&, shared_ptr<IUser>& currentUser) = 0;
};

#endif