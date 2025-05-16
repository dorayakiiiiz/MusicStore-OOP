/**
 * @file IController.h
 * @brief Header file for the IController interface
 * 
 * @details Defines the common interface for all controller classes in the system,
 *          establishing a contract for menu functionality implementation
 */

#ifndef _ICONTROLLER_H_
#define _ICONTROLLER_H_

#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Cart.h"
#include "Discount.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <conio.h>

#include "MusicService.h"
#include "UserService.h"
#include "OrderService.h"
#include "DiscountService.h"
#include "CartService.h"
#include "AuthService.h"

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
    virtual void menu(shared_ptr<User>& currentUser) = 0;
};

#endif