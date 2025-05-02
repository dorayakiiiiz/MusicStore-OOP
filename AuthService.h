#ifndef _AUTHENTICATION_H_
#define _AUTHENTICATION_H_
#include "User.h"
#include <vector>
#include <memory>
using std::vector, std::shared_ptr, std::make_shared;

// Service class for user authentication operations
class Authentication {
public:
    // Register a new user with username, password and role
    // Returns true if registration is successful, false if username already exists
    static bool registerUser(vector<shared_ptr<IUser>>&, const string&, const string&, const string&);
    
    // Authenticate a user with username and password
    // Returns a pointer to the user if authentication succeeds, nullptr otherwise
    static shared_ptr<IUser> loginUser(const vector<shared_ptr<IUser>>&, const string&, const string&);
};

#endif