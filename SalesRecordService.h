#ifndef _SALES_RECORD_SERVICE_H_
#define _SALES_RECORD_SERVICE_H_
#include <vector>
#include "ISalesRecordRepository.h"
#include "Registry.h"
#include "SalesRecord.h"
#include "Cart.h"

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
     * @brief Get all sales records in the system
     */
    void trackingRevenue();

    /**
     * @brief add the items purchased to the sales record
     */
    void addToRecord(const Cart& cart);
};

#endif