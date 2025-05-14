/**
 * @file User.cpp
 * @brief Implementation file for User classes
 * 
 * @details Contains implementations for the user hierarchy including
 *          User interface and derived Admin and Customer classes
 */

#include "User.h"

// Constructor for the base user class
User::User(const string& uname, const string& pword) : username(uname), password(pword) {}

// Virtual destructor for the base user class
User::~User() {}

// Get the username of the user
string User::getUsername() const {
    return username;
}

// Get the password of the user
string User::getPassword() const {
    return password;
}

// Convert user to string representation for display
string User::toString() const {
    return username + " - " + password + " - " + (Role::ADMIN == getRole() ? "Admin" : "Customer");
}

// Copy constructor for Customer class
Customer::Customer(const Customer& other) : User(other.getUsername(), other.getPassword()) {}

// Constructor for Customer class
Customer::Customer(const string& uname, const string& pword) : User(uname, pword) {}

// Implementation of getRole() for Customer, returns "Customer"
Role Customer::getRole() const {
    return Role::CUSTOMER;
}

// Constructor for Admin class
Admin::Admin(const string& uname, const string& pword) : User(uname, pword) {}

// Copy constructor for Admin class
Admin::Admin(const Admin& other) : User(other.getUsername(), other.getPassword()) {}

// Implementation of getRole() for Admin, returns "Admin"
Role Admin::getRole() const {
    return Role::ADMIN;
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


