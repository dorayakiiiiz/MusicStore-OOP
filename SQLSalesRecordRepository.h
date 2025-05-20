#ifndef _SQL_SALES_RECORD_REPOSITORY_H_
#define _SQL_SALES_RECORD_REPOSITORY_H_
#include "ISalesRecordRepository.h"
#include "DatabaseConnector.h"

/**
 * @brief SQL implementation of the sales record repository
 */
class SqlSalesRecordRepository : public ISalesRecordRepository {
public:
    /**
     * @brief Constructor for SqlSalesRecordRepository
     */
    SqlSalesRecordRepository();

    /**
     * Destructor for SqlSalesRecordRepository
     */
    virtual ~SqlSalesRecordRepository();

    /**
     * @brief Get all sales records
     *
     * @return std::vector<SalesRecord> Collection of all sales records
     */
    std::vector<SalesRecord> getAll() override;

    /**
     * @brief Add a new sales record
     *
     * @param record The sales record to add
     * @return bool True if successfully added
     */
    bool add(const SalesRecord& record) override;

    /**
     * @brief Get a sales record by ID
     *
     * @param id The ID of the sales record
     * @return SalesRecord The sales record
     */
    SalesRecord getById(int id) override;

    /**
     * @brief Update an existing sales record
     *
     * @param id The ID of the sales record to update
     * @param record The updated sales record
     * @return bool True if successfully updated
     */
    bool updateById(int id, const SalesRecord& record) override;

    /**
     * @brief Delete a sales record by ID
     *
     * @param id The ID of the sales record to delete
     * @return bool True if successfully deleted
     */
    bool deleteById(int id) override;

};

#endif

// /**
//  * @brief SQL implementation of the order repository
//  */
// class SqlOrderRepository : public IOrderRepository {
// public:
//     /**
//      * @brief Constructor for SqlOrderRepository
//      */
//     SqlOrderRepository();

//     /**
//      * @brief Destructor for SqlOrderRepository
//      */
//     virtual ~SqlOrderRepository();

//     /**
//      * @brief Get all order records
//      *
//      * @return vector<Order> Collection of all order records
//      */
//     vector<Order> getAll() override;

//     /**
//      * @brief Get an order record by ID
//      *
//      * @param id The ID of the order record
//      * @return Order The order record
//      */
//     Order getById(int id) override;

//     /**
//      * @brief Add a new order record
//      *
//      * @param order The order record to add
//      * @return bool True if successfully added
//      */
//     bool add(const Order& order) override;

//     /**
//      * @brief Update an existing order record
//      *
//      * @param id The ID of the order record to update
//      * @param order The updated order record
//      * @return bool True if successfully updated
//      */
//     bool updateById(int id, const Order& order) override;

//     /**
//      * @brief Delete an order record by ID
//      *
//      * @param id The ID of the order record to delete
//      * @return bool True if successfully deleted
//      */
//     bool deleteById(int id) override;
// };

// #endif