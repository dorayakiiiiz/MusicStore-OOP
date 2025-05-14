#ifndef _IUSER_REPOSITORY_H_
#define _IUSER_REPOSITORY_H_

#include "IRepository.h"
#include "User.h"

class IUserRepository : public IRepository<User> {
public:
    virtual ~IUserRepository() = default;

    /**
     * @brief Get all user records
     *
     * @return std::vector<User> Collection of all user records
     */
    virtual std::vector<User> getAll() = 0;

    /**
     * @brief Get a user record by ID
     *
     * @param id The ID of the user record
     * @return User The user record
     */
    virtual User getById(int id) = 0;

    /**
     * @brief Add a new user record
     *
     * @param user The user record to add
     * @return bool True if successfully added
     */
    virtual bool add(const User& user) = 0;

    /**
     * @brief Update an existing user record
     *
     * @param id The ID of the user record to update
     * @param user The updated user record
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const User& user) = 0;

    /**
     * @brief Delete a user record by ID
     *
     * @param id The ID of the user record to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;
};

#endif
