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

/**
 * @brief Interface for controller classes that handle user interactions
 * 
 * @details Defines the common interface for different user role controllers
 */
class IController {
public:
    /**
     * @brief Menu method implemented by concrete controllers to handle user interactions
     * 
     * @param items Reference to the store's music inventory
     * @param users Reference to the system's user accounts
     * @param orders Reference to the system's order history
     * @param discounts Reference to available discount vouchers
     * @param currentUser Reference to the currently logged-in user
     */
    virtual void menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>& discounts, shared_ptr<IUser>& currentUser) = 0;
};

#endif