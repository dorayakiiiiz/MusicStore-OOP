#ifndef SQL_ORDER_REPOSITORY_H
#define SQL_ORDER_REPOSITORY_H

#include <vector>
#include <string>

#include "IOrderRepository.h"
#include "DatabaseConnector.h"

/**
 * @brief SQL implementation of the order repository
 */
class SqlOrderRepository : public IOrderRepository {
private:
    /**
     * @brief Database connector for SQL operations
     */
    DatabaseConnector dbConnector;
public:
    /**
     * @brief Constructor for SqlOrderRepository
     */
    SqlOrderRepository();

    /**
     * @brief Destructor for SqlOrderRepository
     */
    virtual ~SqlOrderRepository();

    /**
     * @brief Get all order records
     *
     * @return vector<Order> Collection of all order records
     */
    vector<Order> getAll() override;

    /**
     * @brief Get an order record by ID
     *
     * @param id The ID of the order record
     * @return Order The order record
     */
    // Order getById(int id) override;

    /**
     * @brief Add a new order record
     *
     * @param order The order record to add
     * @return bool True if successfully added
     */
    bool add(const Order& order) override;

    /**
     * @brief Update an existing order record
     *
     * @param id The ID of the order record to update
     * @param order The updated order record
     * @return bool True if successfully updated
     */
    // bool updateById(int id, const Order& order) override;

    /**
     * @brief Delete an order record by ID
     *
     * @param id The ID of the order record to delete
     * @return bool True if successfully deleted
     */
    // bool deleteById(int id) override;
};

#endif