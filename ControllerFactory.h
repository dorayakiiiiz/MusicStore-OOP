#ifndef _CONTROLLER_FACTORY_H_
#define _CONTROLLER_FACTORY_H_

#include "IController.h"

#include <string>
#include <memory>
using std::string, std::shared_ptr, std::make_shared;


class ControllerFactory {
public:
    static shared_ptr<IController> createController(const string&);
};
#endif