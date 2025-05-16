#ifndef _IUSER_REPOSITORY_H_
#define _IUSER_REPOSITORY_H_

#include "IRepository.h"
#include "User.h"

#include <memory>

using std::shared_ptr;

class IUserRepository : public IRepository<shared_ptr<User>> {
public:
    virtual ~IUserRepository() = default;

    /**
     * @brief Get all user records
     *
     * @return std::vector<shared_ptr<User>> Collection of all user records
     */
    virtual vector<shared_ptr<User>> getAll() = 0;

    /**
     * @brief Get a user record by ID
     *
     * @param id The ID of the user record
     * @return shared_ptr<User> The user record
     */
    virtual shared_ptr<User> getById(int id) = 0;

    /**
     * @brief Add a new user record
     *
     * @param user The user record to add
     * @return bool True if successfully added
     */
    virtual bool add(const shared_ptr<User>& user) = 0;

    /**
     * @brief Update an existing user record
     *
     * @param id The ID of the user record to update
     * @param user The updated user record
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const shared_ptr<User>& user) = 0;

    /**
     * @brief Delete a user record by ID
     *
     * @param id The ID of the user record to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;
};

#endif
