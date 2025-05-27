#ifndef _SQL_DAO_H_
#define _SQL_DAO_H_

#include "IDataProvider.h"
#include "SQLMusicRepository.h"
#include "SQLUserRepository.h"
#include "SQLOrderRepository.h"
#include "SQLDiscountRepository.h"
#include "SQLSalesRecordRepository.h"

/**
 * @brief SQL Data Access Object
 *
 * @details Implements the IDataProvider interface for SQL database access
 */
class SqlDao : public IDataProvider {
public:
    /**
     * @brief Constructor for SqlDao
     */
    SqlDao() = default;

    /**
     * @brief Destructor for SqlDao
     */
    ~SqlDao() override = default;

    /**
     * @brief Get the music repository
     *
     * @return shared_ptr<IRepository<Music>> Reference to the music repository
     * @details This method returns a shared pointer to the music repository
     */
    shared_ptr<IRepository<Music>> music() override;

    /**
     * @brief Get the user repository
     *
     * @return shared_ptr<IRepository<shared_ptr<User>>> Reference to the user repository
     * @details This method returns a shared pointer to the user repository
     */
    shared_ptr<IRepository<shared_ptr<User>>> user() override;

    /**
     * @brief Get the order repository
     *
     * @return shared_ptr<IRepository<Order>> Reference to the order repository
     * @details This method returns a shared pointer to the order repository
     */
    shared_ptr<IRepository<Order>> order() override;

    /**
     * @brief Get the discount repository
     *
     * @return shared_ptr<IRepository<shared_ptr<Discount>>> Reference to the discount repository
     * @details This method returns a shared pointer to the discount repository
     */
    shared_ptr<IRepository<shared_ptr<Discount>>> discount() override;

    /**
     * @brief Get the sales record repository
     *
     * @return shared_ptr<IRepository<SalesRecord>> Reference to the sales record repository
     * @details This method returns a shared pointer to the sales record repository
     */
    shared_ptr<IRepository<SalesRecord>> salesRecord() override;

};

#endif

// IDataProvider* dataProvider = new SqlDao();
// vector<Music> items = dataProvider->music()->getAll();