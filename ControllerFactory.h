#ifndef _CONTROLLER_FACTORY_H_
#define _CONTROLLER_FACTORY_H_

#include "IController.h"

#include <string>
#include <memory>
using std::string, std::shared_ptr, std::make_shared;

/**
 * @brief Factory class for creating controller objects based on user role
 */
class ControllerFactory {
public:
    /**
     * @brief Create a controller based on user role
     * 
     * @param role The role of the user (Admin or Customer)
     * @return shared_ptr<IController> A controller for the specified role
     */
    static shared_ptr<IController> createController(const string&);
};
#endif