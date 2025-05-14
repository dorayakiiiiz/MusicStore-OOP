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
ControllerFactory::ControllerFactory() {
    // Initialize the controller map with instances of AdminController and CustomerController
    controllers[Role::ADMIN] = make_shared<AdminController>();
    controllers[Role::CUSTOMER] = make_shared<CustomerController>();
}

// Create a controller based on user role
shared_ptr<IController> ControllerFactory::createController(Role role) {
    // Check if the requested role exists in the controller map
    if (controllers.find(role) != controllers.end()) {
        return controllers[role]; // Return the corresponding controller instance
    }
    return nullptr; // Return null if the role is not found
}