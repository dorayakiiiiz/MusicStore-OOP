#ifndef _USER_H_
#define _USER_H_

#include "Order.h"
#include <string>
#include <vector>
#include <iostream>
using std::string, std::vector, std::cout;

// Abstract base class for all user types in the system
class IUser {
private:
    string username; // Username for authentication
    string password; // Password for authentication
public:
    virtual ~IUser(); // Virtual destructor for proper inheritance
    IUser(const string&, const string&); // Constructor with username and password
    virtual string getRole() const = 0; // Pure virtual method to get user role
    string getUsername() const; // Get the username
    string getPassword() const; // Get the password
    string toString() const; // Convert user to string representation
};

// Customer user type - regular user with standard privileges
class Customer : public IUser {
public:
    Customer(const string&, const string&); // Constructor with username and password
    Customer(const Customer&); // Copy constructor
    string getRole() const override; // Implementation of getRole() returning "Customer"
};

// Admin user type - privileged user with administrative capabilities
class Admin : public IUser {
private:
    // Static list of valid admin registration passkeys
    inline static vector<string> passKeys = {"23120197", "23120209"};
public:
    Admin(const string&, const string&); // Constructor with username and password
    Admin(const Admin&); // Copy constructor
    string getRole() const override; // Implementation of getRole() returning "Admin"
    static bool isValidPasskey(const string&); // Validates if a passkey is authorized for admin registration
};

#endif