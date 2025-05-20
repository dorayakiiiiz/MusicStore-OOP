#ifndef _I_SALES_RECORD_REPOSITORY_H_
#define _I_SALES_RECORD_REPOSITORY_H_
#include "IRepository.h"
#include "SalesRecord.h"

class ISalesRecordRepository : public IRepository<SalesRecord> {
public:
    virtual ~ISalesRecordRepository() = default;

    /**
     * @brief Get all sales records
     *
     * @return std::vector<SalesRecord> Collection of all sales records
     */
    virtual std::vector<SalesRecord> getAll() = 0;

    /**
     * @brief Add a new sales record
     *
     * @param record The sales record to add
     * @return bool True if successfully added
     */
    virtual bool add(const SalesRecord& record) = 0;

    /**
     * @brief Update an existing sales record
     *
     * @param id The ID of the sales record to update
     * @param record The updated sales record
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const SalesRecord& record) = 0;

    /**
     * @brief Delete a sales record by ID
     *
     * @param id The ID of the sales record to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;
};


#endif