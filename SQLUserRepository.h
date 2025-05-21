#ifndef SQL_USER_REPOSITORY_H
#define SQL_USER_REPOSITORY_H
#include <vector>
#include <string>
#include <memory>

#include "IRepository.h"
#include "User.h"
#include "DatabaseConnector.h"

using std::vector, std::shared_ptr, std::make_shared;

/**
 * @brief SQL implementation of the user repository
 */
class SqlUserRepository : public IRepository<shared_ptr<User>> {
public:
    /**
     * @brief Constructor for SqlUserRepository
     */
    SqlUserRepository();

    /**
     * @brief Destructor for SqlUserRepository
     */
    virtual ~SqlUserRepository();

    /**
     * @brief Get all user records
     *
     * @return vector<shared_ptr<User>> Collection of all user records
     */
    vector<shared_ptr<User>> getAll() override;

    /**
     * @brief Get a user record by ID
     *
     * @param id The ID of the user record
     * @return shared_ptr<User> The user record
     */
    shared_ptr<User> getById(int id) override;

    /**
     * @brief Add a new user record
     *
     * @param user The user record to add
     * @return bool True if successfully added
     */
    bool add(const shared_ptr<User>& user) override;

    /**
     * @brief Update an existing user record
     *
     * @param id The ID of the user record to update
     * @param user The updated user record
     * @return bool True if successfully updated
     */
    bool updateById(int id, const shared_ptr<User>& user) override;

    /**
     * @brief Delete a user record by ID
     *
     * @param id The ID of the user record to delete
     * @return bool True if successfully deleted
     */
    bool deleteById(int id) override;
};

#endif