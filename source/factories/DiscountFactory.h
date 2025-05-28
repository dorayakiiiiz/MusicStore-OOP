#ifndef _DISCOUNT_FACTORY_H_
#define _DISCOUNT_FACTORY_H_

#include "../models/Discount.h"
#include "../strategies/DiscountStrategy.h"

#include <memory>
#include <map>

using std::shared_ptr, std::make_shared, std::map;
class DiscountFactory {
private:
    map<DiscountType, shared_ptr<DiscountStrategy>> _strategies; /**< Map to store discount strategies by type */
public:
    /**
     * @brief Constructor for DiscountFactory
     */
    DiscountFactory();

    /**
     * @brief Get a discount strategy by type
     * 
     * @param type The type of discount strategy (e.g., "Percentage", "Fixed")
     * @return shared_ptr<DiscountStrategy> Pointer to the requested strategy
     */
    shared_ptr<DiscountStrategy> getStrategy(DiscountType type);
};

#endif