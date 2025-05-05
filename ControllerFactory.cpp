/**
 * @file ControllerFactory.cpp
 * @brief Implementation of the ControllerFactory class
 * 
 * @details This file contains the implementation of the ControllerFactory class,
 *          which creates the appropriate controller instance (AdminController or
 *          CustomerController) based on the user's role in the system.
 */

#include "ControllerFactory.h"
#include "AdminController.h"
#include "CustomerController.h"

// Constructor for ControllerFactory
ControllerFactory::ControllerFactory(
    MusicService& musicService,
    CartService& cartService,
    OrderService& orderService,
    DiscountService& discountService,
    UserService& userService
) : musicService(musicService), cartService(cartService), orderService(orderService), discountService(discountService), userService(userService) {}

// Create a controller based on user role
shared_ptr<IController> ControllerFactory::createController(const string& role) {
    if ("Admin" == role) {
        return make_shared<AdminController>(
            musicService, 
            userService, 
            orderService
        );
    } else if ("Customer" == role) {
        return make_shared<CustomerController>(
            musicService, 
            cartService, 
            orderService, 
            discountService
        );
    } else {
        return nullptr;
    }
}