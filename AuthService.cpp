/**
 * @file AuthService.cpp
 * @brief Implementation file for the Authentication service
 * 
 * @details Contains implementations for user login, registration and authentication
 *          functionality for the music store system
 */

#include "AuthService.h"
#include "utils.h"

// Register a new user with username, password, and role
bool AuthService::registerUser(vector<shared_ptr<User>>& users, const string& username, const string& password, Role role) {
    // Check if username already exists
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return false;
        }
    }
    
    // Create appropriate user type based on role
    if (Role::CUSTOMER == role) {
        users.push_back(make_shared<Customer>(username, password));
    } else {
        users.push_back(make_shared<Admin>(username, password));
    }
    return true;
}

// Authenticate a user with username and password
shared_ptr<User> AuthService::loginUser(const vector<shared_ptr<User>>& users, const string& username, const string& password) {
    // Search for matching username and password
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            return users[i];
        }
    }
    return nullptr;
}
