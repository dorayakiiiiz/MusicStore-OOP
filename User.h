/**
 * @file User.h
 * @brief Header file for User classes
 * 
 * @details Defines the user class hierarchy, including the IUser interface
 *          and derived Admin and Customer classes
 */

#ifndef _USER_H_
#define _USER_H_

#include "Order.h"
#include <string>
#include <vector>
#include <iostream>
using std::string, std::vector, std::cout;


/**
 * @brief Enumeration for user roles
 * 
 * @details Defines the roles available in the system: Admin and Customer
 */
enum Role {
    ADMIN = 1,
    CUSTOMER = 2
};

/**
 * @brief Abstract base class for all user types in the system
 */
class IUser {
private:
    string username; /**< Username for authentication */
    string password; /**< Password for authentication */
public:
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~IUser();
    
    /**
     * @brief Constructor with username and password
     * 
     * @param username Username for the user
     * @param password Password for the user
     */
    IUser(const string&, const string&);
    
    /**
     * @brief Pure virtual method to get user role
     *
     * @return Role The role of the user
     */
    virtual Role getRole() const = 0;
    
    /**
     * @brief Get the username
     * 
     * @return string The username
     */
    string getUsername() const;
    
    /**
     * @brief Get the password
     * 
     * @return string The password
     */
    string getPassword() const;
    
    /**
     * @brief Convert user to string representation
     * 
     * @return string String representation of the user
     */
    string toString() const;
};

/**
 * @brief Customer user type - regular user with standard privileges
 */
class Customer : public IUser {
public:
    /**
     * @brief Constructor with username and password
     * 
     * @param username Username for the customer
     * @param password Password for the customer
     */
    Customer(const string&, const string&);
    
    /**
     * @brief Copy constructor
     * 
     * @param other The Customer object to copy
     */
    Customer(const Customer&);
    
    /**
     * @brief Implementation of getRole() returning "Customer"
     *
     * @return Role The role "Customer"
     */
    Role getRole() const override;
};

/**
 * @brief Admin user type - privileged user with administrative capabilities
 */
class Admin : public IUser {
private:
    /**
     * @brief Static list of valid admin registration passkeys
     */
    inline static vector<string> passKeys = {"23120197", "23120209"};
public:
    /**
     * @brief Constructor with username and password
     * 
     * @param username Username for the admin
     * @param password Password for the admin
     */
    Admin(const string&, const string&);
    
    /**
     * @brief Copy constructor
     * 
     * @param other The Admin object to copy
     */
    Admin(const Admin&);
    
    /**
     * @brief Implementation of getRole() returning "Admin"
     *
     * @return Role The role "Admin"
     */
    Role getRole() const override;
    
    /**
     * @brief Validates if a passkey is authorized for admin registration
     * 
     * @param key The passkey to validate
     * @return bool True if the passkey is valid
     */
    static bool isValidPasskey(const string&);
};

#endif