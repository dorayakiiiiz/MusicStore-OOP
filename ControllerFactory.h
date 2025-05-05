
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
using std::string, std::shared_ptr, std::make_shared;

/**
 * @brief Factory class for creating controller instances based on user role
 * 
 * @details This class is responsible for creating the appropriate controller instance
 *          based on the user's role (Admin or Customer).
 */

class ControllerFactory {
private:
    MusicService& musicService;  /**< Reference to the music service for inventory operations */
    CartService& cartService;    /**< Reference to the cart service for shopping operations */
    OrderService& orderService;  /**< Reference to the order service for order processing */
    DiscountService& discountService;   /**< Reference to the discount service for voucher management */
    UserService& userService;    /**< Reference to the user service for user management */
    
public:
    /**
     * @brief Constructor for ControllerFactory
     * 
     * @param musicService Reference to music service for inventory operations
     * @param cartService Reference to cart service for shopping operations
     * @param orderService Reference to order service for order processing
     * @param discountService Reference to discount service for voucher management
     * @param userService Reference to user service for user management
     */
    ControllerFactory(
        MusicService& musicService,
        CartService& cartService,
        OrderService& orderService,
        DiscountService& discountService,
        UserService& userService
    );
    
    /**
     * @brief Create a controller based on user role
     * 
     * @param role The role of the user (Admin or Customer)
     * @return shared_ptr<IController> A controller for the specified role
     */
    shared_ptr<IController> createController(const string& role);
};

#endif