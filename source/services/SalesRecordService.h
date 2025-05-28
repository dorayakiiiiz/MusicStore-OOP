#ifndef _SALES_RECORD_SERVICE_H_
#define _SALES_RECORD_SERVICE_H_
#include <vector>
#include "../database/IDataProvider.h"
#include "../database/IRepository.h"
#include "../database/SQLDao.h"
#include "../models/SalesRecord.h"
#include "../models/Cart.h"

#include <vector>
using std::vector;

/**
 * @brief Service class for managing sales records
 * 
 * @details Provides methods for adding, removing, and retrieving sales records
 */
class SalesRecordService {
private:
    inline static shared_ptr<SalesRecordService> _instance = nullptr; /**< Singleton instance of SalesRecordService */

protected:
    /**
     * @brief Private constructor for singleton pattern
     * 
     * @param provider Data provider to access sales record data
     */
    SalesRecordService(shared_ptr<IDataProvider> _provider); /**< Constructor for singleton pattern */

    shared_ptr<IDataProvider> _dataProvider; /**< Data provider for accessing sales record data */
public:

    /**
     * @brief Get the singleton instance of SalesRecordService
     * 
     * @param provider Optional data provider to use
     * @return shared_ptr<SalesRecordService> Pointer to the singleton instance
     */
    static shared_ptr<SalesRecordService> getInstance(shared_ptr<IDataProvider> provider = nullptr);

    /**
     * @brief Default destructor
     */
    ~SalesRecordService() = default;

    /**
     * @brief Get all sales records
     * 
     * @return vector<SalesRecord> Collection of all sales records
     */
    vector<SalesRecord> getAllSalesRecords();


    /**
     * @brief Get total revenue generated from all sales records
     * 
     * @return float Total revenue
     */
    float getTotalRevenue();

    /**
     * @brief add the items purchased to the sales record
     */
    void addToRecord(const Cart& cart);
};

#endif