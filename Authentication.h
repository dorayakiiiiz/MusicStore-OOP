#ifndef _AUTHENTICATION_H_
#define _AUTHENTICATION_H_
#include "User.h"
#include "Database.h"
#include <vector>
#include <memory>
using std::vector, std::shared_ptr, std::make_shared;

class Authentication {
public:
    static void registerCustomer(vector<shared_ptr<Customer>>&);
    static shared_ptr<Customer> loginCustomer(const vector<shared_ptr<Customer>>&);
    static bool loginAdmin();
};

#endif