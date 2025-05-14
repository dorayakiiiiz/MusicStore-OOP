
/************************************************************************************
 * @file ControllerFactory.h
 * @brief Header file for the ControllerFactory class
 * 
 * @details This file contains the declaration of the ControllerFactory class, which is
 *          responsible for creating controller instances based on user roles (Admin or Customer).
 * 
 ************************************************************************************/

#ifndef _CONTROLLER_FACTORY_H_
#define _CONTROLLER_FACTORY_H_

#include "IController.h"
#include "MusicService.h"
#include "CartService.h"
#include "OrderService.h"
#include "DiscountService.h"
#include "UserService.h"

#include <string>
#include <memory>
#include <map>
using std::string, std::shared_ptr, std::make_shared, std::map;

/**
 * @brief Factory class for creating controller instances based on user role
 * 
 * @details This class is responsible for creating the appropriate controller instance
 *          based on the user's role (Admin or Customer).
 */

class ControllerFactory {
private:
    /**
     * @brief Services 
     */
    shared_ptr<MusicService> musicService;
    shared_ptr<CartService> cartService;
    shared_ptr<OrderService> orderService;
    shared_ptr<DiscountService> discountService;
    shared_ptr<UserService> userService;

    map<Role, shared_ptr<IController>> controllers;
public:
    /**
     * @brief Constructor for ControllerFactory
     * 
     * @param musicService Music service for inventory operations
     * @param cartService Cart service for shopping operations
     * @param orderService Order service for order processing
     * @param discountService Discount service for voucher management
     * @param userService User service for user management
     */
    ControllerFactory(
        shared_ptr<MusicService> musicService,
        shared_ptr<CartService> cartService,
        shared_ptr<OrderService> orderService,
        shared_ptr<DiscountService> discountService,
        shared_ptr<UserService> userService
    );
    
    /**
     * @brief Create a controller based on user role
     * 
     * @param role The role of the user (Admin or Customer)
     * @return shared_ptr<IController> A controller for the specified role
     */
    shared_ptr<IController> createController(Role role);
};

#endif