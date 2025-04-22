#include "Authentication.h"
#include "utils.h"

// git commit commit

bool Authentication::registerCustomer(vector<shared_ptr<Customer>>& customers, const string& username, const string& password) {
    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i]->getUsername() == username) {
            return false;
        }
    }
    customers.push_back(make_shared<Customer>(username, password));
    return true;
}

shared_ptr<Customer> Authentication::loginCustomer(const vector<shared_ptr<Customer>>& customers, const string& username, const string& password) {
    
    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i]->getUsername() == username && customers[i]->getPassword() == password) {
            return customers[i];
        }
    }
    return nullptr;
}

bool Authentication::loginAdmin(const string& passkey) {

    if (AdminPasskey::getInstance()->isValid(passkey)) {
        return true;
    } else { 
        return false;
    }
}