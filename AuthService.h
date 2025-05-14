/**
 * @file AuthService.h
 * @brief Header file for the Authentication service
 * 
 * @details Defines the Authentication class which handles user login,
 *          registration and validation operations
 */

#ifndef _AUTH_SERVICE_H_
#define _AUTH_SERVICE_H_
#include "User.h"
#include <vector>
#include <memory>
using std::vector, std::shared_ptr, std::make_shared;

/**
 * @brief Service class for user authentication operations
 */
class AuthService {
public:
    /**
     * @brief Register a new user with username, password and role
     * 
     * @param users Vector of existing users to add the new user to
     * @param username Username for the new user
     * @param password Password for the new user 
     * @param role Role of the new user (Admin or Customer)
     * @return bool True if registration successful, false if username already exists
     */
    bool registerUser(vector<shared_ptr<User>>&, const string&, const string&, Role);
    
    /**
     * @brief Authenticate a user with username and password
     * 
     * @param users Vector of existing users to check against
     * @param username Username to authenticate
     * @param password Password to verify
     * @return shared_ptr<User> Pointer to the authenticated user or nullptr if authentication failed
     */
    shared_ptr<User> loginUser(const vector<shared_ptr<User>>&, const string&, const string&);
};

#endif