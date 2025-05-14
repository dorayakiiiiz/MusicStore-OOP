#ifndef _IORDER_REPOSITORY_H_
#define _IORDER_REPOSITORY_H_

#include "IRepository.h"
#include "Order.h"

class IOrderRepository : public IRepository<Order> {
public:
    virtual ~IOrderRepository() = default;

    /**
     * @brief Get all order records
     *
     * @return std::vector<Order> Collection of all order records
     */
    virtual std::vector<Order> getAll() = 0;

    /**
     * @brief Get an order record by ID
     *
     * @param id The ID of the order record
     * @return Order The order record
     */
    virtual Order getById(int id) = 0;

    /**
     * @brief Add a new order record
     *
     * @param order The order record to add
     * @return bool True if successfully added
     */
    virtual bool add(const Order& order) = 0;

    /**
     * @brief Update an existing order record
     *
     * @param id The ID of the order record to update
     * @param order The updated order record
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const Order& order) = 0;

    /**
     * @brief Delete an order record by ID
     *
     * @param id The ID of the order record to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;
};

#endif