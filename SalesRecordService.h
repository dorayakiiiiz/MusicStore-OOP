#ifndef _SALES_RECORD_SERVICE_H_
#define _SALES_RECORD_SERVICE_H_
#include <vector>
#include "IDataProvider.h"
#include "IRepository.h"
#include "SQLDao.h"
#include "SalesRecord.h"
#include "Cart.h"

#include <vector>
using std::vector;

/**
 * @brief Service class for managing sales records
 * 
 * @details Provides methods for adding, removing, and retrieving sales records
 */
class SalesRecordService {
private:
    inline static shared_ptr<SalesRecordService> instance = nullptr; /**< Singleton instance of SalesRecordService */

    shared_ptr<IDataProvider> dataProvider; /**< Data provider for accessing sales record data */
    
    SalesRecordService(); /**< Private constructor for singleton pattern */
public:

    /**
     * @brief Get the singleton instance of OrderService
     * 
     * @return shared_ptr<SalesRecordService> Pointer to the singleton instance
     */
    static shared_ptr<SalesRecordService> getInstance();

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