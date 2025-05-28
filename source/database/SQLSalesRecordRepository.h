#ifndef _SQL_SALES_RECORD_REPOSITORY_H_
#define _SQL_SALES_RECORD_REPOSITORY_H_

#include "IRepository.h"
#include "DatabaseConnector.h"
#include "../models/SalesRecord.h"
#include <vector>

/**
 * @brief SQL implementation of the sales record repository
 */
class SqlSalesRecordRepository : public IRepository<SalesRecord> {
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