#include "ControllerFactory.h"
#include "AdminController.h"
#include "CustomerController.h"

shared_ptr<IController> ControllerFactory::createController(const string& role) {
    if (role == "Admin") {
        return make_shared<AdminController>();
    } else if (role == "Customer") {
        return make_shared<CustomerController>();
    } else {
        return nullptr;
    }
}