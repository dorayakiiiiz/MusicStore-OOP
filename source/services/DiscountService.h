/**
 * @file DiscountService.h
 * @brief Header file for the DiscountService class
 * 
 * @details Defines the DiscountService class which manages discount vouchers
 *          for the music store system
 */

#ifndef _DISCOUNT_SERVICE_H_
#define _DISCOUNT_SERVICE_H_

#include "../models/Discount.h"
#include "../database/IDataProvider.h"
#include "../strategies/DiscountStrategy.h"
#include "../factories/DiscountFactory.h"
#include <vector>
#include <memory>
#include <string>
#include <random>

using std::vector, std::shared_ptr, std::string, std::make_shared, std::make_unique;

/**
 * @brief Service class for managing discounts in the system
 */
class DiscountService {
private:
    inline static shared_ptr<DiscountService> _instance = nullptr; /**< Singleton instance of DiscountService */

protected:

    DiscountService(shared_ptr<IDataProvider> _provider); /**< Constructor for singleton pattern */

    shared_ptr<IDataProvider> _dataProvider; /**< Data provider for accessing discount data */
public:

    /**
     * @brief Get the singleton instance of DiscountService
     * 
     * @return shared_ptr<DiscountService> Pointer to the singleton instance
     */
    static shared_ptr<DiscountService> getInstance(shared_ptr<IDataProvider> provider = nullptr);

    /**
     * @brief Default destructor
     */
    ~DiscountService() = default;

    /**
     * @brief Get all available discount vouchers
     * 
     * @return vector<shared_ptr<Discount>> Vector of all discount vouchers
     */
    vector<shared_ptr<Discount>> getAllDiscounts();
    /**
     * @brief Apply a discount to a total price
     * 
     * @param voucher The discount to apply
     * @param total The original total price
     * @return float The price after applying the discount
     */
    float applyDiscount(const shared_ptr<Discount>& voucher, float total);
    
    /**
     * @brief Check if a discount exists in the list of vouchers
     * 
     * @param vouchers Vector of existing discount vouchers
     * @param voucher The discount voucher to check
     * @return bool True if the voucher exists in the list, false otherwise
     */
    bool isValidDiscount(const vector<shared_ptr<Discount>>& vouchers, 
                               const shared_ptr<Discount>& voucher);
    
    /**
     * @brief Get all valid discounts for a specific username
     * 
     * @param vouchers Vector of all available discount vouchers
     * @param username Username to filter vouchers by
     * @return vector<shared_ptr<Discount>> Vector of discount vouchers valid for the specified user
     */
    vector<shared_ptr<Discount>> loadValidDiscounts(
        const vector<shared_ptr<Discount>>& vouchers, const string& username);
        
    /**
     * @brief Remove a discount voucher from the repository
     * 
     * @param shared_ptr<Discount> discount The discount voucher to remove
     */    
    void removeDiscount(const shared_ptr<Discount>& discount);

    /**
     * @brief Generate a random discount code
     * 
     * @return string A randomly generated discount code
     */
    virtual string generateRandomCode();

    /**
     * @brief Create a new discount voucher
     * 
     * @param username The username associated with the discount
     * @param type The type of discount (percentage or fixed amount)
     * @param discountValue The value of the discount
     * @return shared_ptr<Discount> Pointer to the created discount voucher
     */
    shared_ptr<Discount> createDiscount(const string& username, DiscountType type, int discountValue);
};

#endif