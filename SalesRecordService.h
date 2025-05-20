#ifndef _SALES_RECORD_SERVICE_H_
#define _SALES_RECORD_SERVICE_H_
#include <vector>
#include "ISalesRecordRepository.h"
#include "Registry.h"
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
public:

    /**
     * @brief Default constructor
     */
    SalesRecordService() = default;

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