#ifndef _I_DATA_PROVIDER_H_
#define _I_DATA_PROVIDER_H_

#include "IRepository.h"
#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Discount.h"
#include "SalesRecord.h"

#include <memory>
using std::shared_ptr;

/**
 * @brief Interface for data provider classes
 * 
 * @details Defines the common interface for different data providers
 */
class IDataProvider {
public:

    /**
     * @brief Virtual destructor for cleanup
     */
    virtual ~IDataProvider() = default;

    /**
     * @brief Get the music repository
     *
     * @return IRepository<Music>& Reference to the music repository
     */
    virtual shared_ptr<IRepository<Music>> music() = 0;

    /**
     * @brief Get the user repository
     *
     * @return shared_ptr<IRepository<User>> Reference to the user repository
     */
    virtual shared_ptr<IRepository<shared_ptr<User>>> user() = 0;

    /**
     * @brief Get the order repository
     *
     * @return shared_ptr<IRepository<Order>> Reference to the order repository
     */
    virtual shared_ptr<IRepository<Order>> order() = 0;

    /**
     * @brief Get the discount repository
     *
     * @return shared_ptr<IRepository<shared_ptr<Discount>>> Reference to the discount repository
     */
    virtual shared_ptr<IRepository<shared_ptr<Discount>>> discount() = 0;

    /**
     * @brief Get the sales record repository
     *
     * @return shared_ptr<IRepository<SalesRecord>> Reference to the sales record repository
     */
    virtual shared_ptr<IRepository<SalesRecord>> salesRecord() = 0;
};

#endif