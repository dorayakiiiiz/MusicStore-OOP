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
    if (role == "Admin") {
        return make_shared<AdminController>(
            musicService, 
            userService, 
            orderService
        );
    } else if (role == "Customer") {
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