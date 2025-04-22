#ifndef _AUTHENTICATION_H_
#define _AUTHENTICATION_H_
#include "User.h"
#include <vector>
#include <memory>
using std::vector, std::shared_ptr, std::make_shared;

class Authentication {
public:
    static bool registerCustomer(vector<shared_ptr<Customer>>&, const string&, const string&);
    static shared_ptr<Customer> loginCustomer(const vector<shared_ptr<Customer>>&, const string&, const string&);
    static bool loginAdmin(const string&);
};

#endif