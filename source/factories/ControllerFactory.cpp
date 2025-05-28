/**
 * @file ControllerFactory.cpp
 * @brief Implementation of the ControllerFactory class
 * 
 * @details This file contains the implementation of the ControllerFactory class,
 *          which creates the appropriate controller instance (AdminController or
 *          CustomerController) based on the user's role in the system.
 */

#include "ControllerFactory.h"
#include "../controllers/AdminController.h"
#include "../controllers/CustomerController.h"

// Constructor for ControllerFactory
ControllerFactory::ControllerFactory() {
    // Initialize the controller map with instances of AdminController and CustomerController
    _controllers[Role::ADMIN] = make_shared<AdminController>();
    _controllers[Role::CUSTOMER] = make_shared<CustomerController>();
}

// Create a controller based on user role
shared_ptr<IController> ControllerFactory::createController(Role role) {
    // Check if the requested role exists in the controller map
    if (_controllers.find(role) != _controllers.end()) {
        return _controllers[role]; // Return the corresponding controller instance
    }
    return nullptr; // Return null if the role is not found
}