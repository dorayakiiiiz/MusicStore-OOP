#ifndef _AUTH_MANAGER_H_
#define _AUTH_MANAGER_H_
#include "User.h"
#include "DatabaseManager.h"
#include <vector>
#include <memory>
using std::vector, std::shared_ptr, std::make_shared;

class AuthManager {
public:
    static void registerCustomer(vector<shared_ptr<Customer>>&);
    static shared_ptr<Customer> loginCustomer(const vector<shared_ptr<Customer>>&);
    static bool loginAdmin();
};

#endif