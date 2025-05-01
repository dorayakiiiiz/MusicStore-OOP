#include "User.h"

IUser::IUser(const string& uname, const string& pword) : username(uname), password(pword) {}

IUser::~IUser() {}

string IUser::getUsername() const {
    return username;
}



string IUser::getPassword() const {
    return password;
}

string IUser::toString() const {
    return username + " - " + password + " - " + getRole();
}

Customer::Customer(const Customer& other) : IUser(other.getUsername(), other.getPassword()) {}

Customer::Customer(const string& uname, const string& pword) : IUser(uname, pword) {}

string Customer::getRole() const {
    return "Customer";
}

Admin::Admin(const string& uname, const string& pword) : IUser(uname, pword) {}

Admin::Admin(const Admin& other) : IUser(other.getUsername(), other.getPassword()) {}

string Admin::getRole() const {
    return "Admin";
}

bool Admin::isValidPasskey(const string& key) {
    for (const auto& passKey : passKeys) {
        if (passKey == key) {
            return true;
        }
    }
    return false;
}


// bool AdminPasskey::isValid(const string& key) {
//     for (int i = 0; i < passKeys.size(); ++i) {
//         if (passKeys[i] == key) {
//             return true;
//         }
//     }
//     return false;
// }

// void AdminPasskey::addPasskey(const string& pass) {
//     passKeys.push_back(pass);
// }


