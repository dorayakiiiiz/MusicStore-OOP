#ifndef _CUSTOMER_DAO_H_
#define _CUSTOMER_DAO_H_
#include "User.h"
#include <vector>
#include <memory>
using std::vector, std::shared_ptr, std::make_shared;

class CustomerDAO {
public:
    static void loadCustomers(vector<shared_ptr<Customer>>&);
    static void saveCustomers(const vector<shared_ptr<Customer>>&);
};

#endif