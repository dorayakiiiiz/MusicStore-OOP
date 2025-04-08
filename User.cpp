#include "User.h"

Customer::Customer(const string& uname, const string& pword) {
    username = uname;
    password = pword;
}

string Customer::getRole() const {
    return "Customer";
}

string Customer::getUsername() const {
    return username;
}

string Customer::getPassword() const {
    return password;
}

void Customer::addPurchase(const string& item) {
    purchaseHistory.push_back(item);
}

AdminPasskey* AdminPasskey::getInstance() {
    if (instance == nullptr) {
        instance = new AdminPasskey();
    }
    return instance;
}

AdminPasskey::AdminPasskey() {
    passKeys = {"VanSy", "NhatAnh"};
}

bool AdminPasskey::isValid(const string& pass) const {
    for (int i = 0; i < passKeys.size(); ++i) {
        if (passKeys[i] == pass) {
            return true;
        }
    }
    return false;
}

void AdminPasskey::addPassket(const string& pass) {
    passKeys.push_back(pass);
}

Admin::Admin() {
    adminPasskey = AdminPasskey::getInstance();
}

string Admin::getRole() const {
    return "Admin";
}