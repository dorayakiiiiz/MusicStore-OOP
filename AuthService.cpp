/**
 * @file AuthService.cpp
 * @brief Implementation file for the Authentication service
 * 
 * @details Contains implementations for user login, registration and authentication
 *          functionality for the music store system
 */

#include "AuthService.h"
#include "IDataProvider.h"
#include "SQLDao.h"
#include "utils.h"

// Constructor
AuthService::AuthService() {
    dataProvider = make_shared<SqlDao>();
}

// get the singleton instance of AuthService
shared_ptr<AuthService> AuthService::getInstance() {
    if (instance == nullptr) {
        instance = shared_ptr<AuthService>(new AuthService());
    }
    return instance;
}

// Register a new user with username, password, and role
bool AuthService::registerUser(const string& username, const string& password, Role role) {
    // Get all users from the repository
    vector<shared_ptr<User>> users = dataProvider->user()->getAll();
    // Check if username already exists
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return false;
        }
    }
    
    shared_ptr<User> newUser;
    // Create a new user based on the role
    if (Role::CUSTOMER == role) {
        newUser = make_shared<Customer>(username, password);
    } else {
        newUser = make_shared<Admin>(username, password);
    }
    // Save the new user to the repository
    bool success = dataProvider->user()->add(newUser);
    return success;
}

// Authenticate a user with username and password
shared_ptr<User> AuthService::loginUser(const string& username, const string& password) {
    // Get all users from the repository
    vector<shared_ptr<User>> users = dataProvider->user()->getAll();
    // Search for matching username and password
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            return users[i];
        }
    }
    return nullptr;
}
