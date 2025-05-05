/**
 * @file User.cpp
 * @brief Implementation file for User classes
 * 
 * @details Contains implementations for the user hierarchy including
 *          IUser interface and derived Admin and Customer classes
 */

#include "User.h"

// Constructor for the base user class
IUser::IUser(const string& uname, const string& pword) : username(uname), password(pword) {}

// Virtual destructor for the base user class
IUser::~IUser() {}

// Get the username of the user
string IUser::getUsername() const {
    return username;
}

// Get the password of the user
string IUser::getPassword() const {
    return password;
}

// Convert user to string representation for display
string IUser::toString() const {
    return username + " - " + password + " - " + getRole();
}

// Copy constructor for Customer class
Customer::Customer(const Customer& other) : IUser(other.getUsername(), other.getPassword()) {}

// Constructor for Customer class
Customer::Customer(const string& uname, const string& pword) : IUser(uname, pword) {}

// Implementation of getRole() for Customer, returns "Customer"
string Customer::getRole() const {
    return "Customer";
}

// Constructor for Admin class
Admin::Admin(const string& uname, const string& pword) : IUser(uname, pword) {}

// Copy constructor for Admin class
Admin::Admin(const Admin& other) : IUser(other.getUsername(), other.getPassword()) {}

// Implementation of getRole() for Admin, returns "Admin"
string Admin::getRole() const {
    return "Admin";
}

// Static method to validate admin registration passkeys
bool Admin::isValidPasskey(const string& key) {
    for (const auto& passKey : passKeys) {
        if (passKey == key) {
            return true;
        }
    }
    return false;
}


