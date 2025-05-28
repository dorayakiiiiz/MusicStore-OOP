#ifndef _USER_SERVICE_H_
#define _USER_SERVICE_H_

#include "../models/User.h"
#include "../database/IDataProvider.h"
#include <vector>
#include <memory>
#include <string>

using std::vector, std::string, std::shared_ptr, std::make_shared;

/**
 * @brief Service class for user-related operations
 * 
 * @details Provides methods to manage user accounts, including deletion and searching by username
 */
class UserService {
private:
    inline static shared_ptr<UserService> _instance = nullptr; /**< Singleton instance of UserService */

protected:
    UserService(shared_ptr<IDataProvider> _provider); /**< Constructor for singleton pattern */
    
    shared_ptr<IDataProvider> _dataProvider; /**< Data provider for accessing user data */

public:

    /**
     * @brief Get the singleton instance of UserService
     * 
     * @param provider Optional data provider to use
     * @return shared_ptr<UserService> Pointer to the singleton instance
     */
    static shared_ptr<UserService> getInstance(shared_ptr<IDataProvider> provider = nullptr);

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
    // bool addUser(const shared_ptr<User>& user);

    
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
     * @brief Get all customer accounts
     * 
     * @return vector<shared_ptr<User>> Vector of all customer accounts
     */
    vector<shared_ptr<User>> getAllCustomers();
};

#endif