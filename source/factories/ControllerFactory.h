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

#include "../controllers/IController.h"
#include "../services/MusicService.h"
#include "../services/CartService.h"
#include "../services/OrderService.h"
#include "../services/DiscountService.h"
#include "../services/UserService.h"

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
    map<Role, shared_ptr<IController>> _controllers; /**< Map to store controller instances */
public:
    /**
     * @brief Constructor for ControllerFactory
     */
    ControllerFactory();
    
    /**
     * @brief Create a controller based on user role
     * 
     * @param role The role of the user (Admin or Customer)
     * @return shared_ptr<IController> A controller for the specified role
     */
    shared_ptr<IController> createController(Role role);
};

#endif