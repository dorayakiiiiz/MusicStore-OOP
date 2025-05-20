#ifndef _USER_SERVICE_H_
#define _USER_SERVICE_H_

#include "User.h"
#include <vector>
#include <string>
#include <memory>

using std::vector, std::string, std::shared_ptr;

/**
 * @brief Service class for user-related operations
 * 
 * @details Provides methods to manage user accounts, including deletion and searching by username
 */
class UserService {
public:
    /**
     * @brief Default constructor
     */
    UserService() = default;

    /**
     * @brief Default destructor
     */
    ~UserService() = default;

    /**
     * @brief Get all user accounts
     * 
     * @return vector<shared_ptr<User>> Vector of all user accounts
     */
    vector<shared_ptr<User>> getAllUsers();

    /**
     * @brief Add a new user account
     * 
     * @param user User object to add
     * @return bool True if successful, false if user already exists
     */
    bool addUser(const shared_ptr<User>& user);

    
    /**
     * @brief Get a user account by ID
     * 
     * @param id ID of the user account to retrieve
     * @return shared_ptr<User> Pointer to the user account, or nullptr if not found
     */
    shared_ptr<User> getUserById(int id);

    /**
     * @brief Delete a user account by username
     * 
     * @param users Reference to the vector of user accounts
     * @param username Username of the account to delete
     * @return bool True if successful, false if user not found
     */
    bool deleteUserById(int id);
    
    /**
     * @brief Find a user by username
     * 
     * @param users Vector of user accounts to search in
     * @param username Username to search for
     * @return int Index of the found user or -1 if not found
     */
    int findUserByUsername(const vector<shared_ptr<User>>& users, const string& username);
    

};

#endif