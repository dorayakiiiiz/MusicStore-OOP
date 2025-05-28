#ifndef _IREPOSITORY_H_
#define _IREPOSITORY_H_

#include <vector>
using std::vector;

template<class T>
class IRepository {
public:
    /**
     * @brief Virtual destructor for cleanup
     */
    virtual ~IRepository() = default;
    /**
     * @brief Get all entities of type T
     *
     * @return std::vector<T> Collection of all entities
     */
    virtual vector<T> getAll() = 0;

    /**
     * @brief Get entity by ID
     * 
     * @param id The ID of the entity to retrieve
     * @return T The retrieved entity
     */
    virtual T getById(int id) = 0;

    /**
     * @brief Add a new entity
     * 
     * @param entity The entity to add
     * @return bool True if successfully added
     */
    virtual bool add(const T& entity) = 0;

    /**
     * @brief Update an existing entity
     * 
     * @param id The ID of the entity to update
     * @param entity The updated entity
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const T& entity) = 0;

    /**
     * @brief Delete an entity by ID
     * 
     * @param id The ID of the entity to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;

};

#endif