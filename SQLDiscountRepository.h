#ifndef _SQL_DISCOUNT_REPOSITORY_H_
#define _SQL_DISCOUNT_REPOSITORY_H_

#include <vector>
#include <string>

using std::vector;

#include "IRepository.h"
#include "DatabaseConnector.h"
#include "Discount.h"
#include "DiscountStrategy.h"
#include "DiscountFactory.h"

/**
 * @brief SQL implementation of the discount repository
 */
class SqlDiscountRepository : public IRepository<shared_ptr<Discount>> {
public:
    /**
     * @brief Constructor for SqlDiscountRepository
     */
    SqlDiscountRepository();

    /**
     * @brief Destructor for SqlDiscountRepository
     */
    virtual ~SqlDiscountRepository();

    /**
     * @brief Get all discount records
     *
     * @return vector<shared_ptr<Discount>> Collection of all discount records
     */
    vector<shared_ptr<Discount>> getAll() override;

    /**
     * @brief Get a discount record by ID
     *
     * @param id The ID of the discount record
     * @return shared_ptr<Discount> The discount record
     */
    shared_ptr<Discount> getById(int id) override;

    /**
     * @brief Add a new discount record
     *
     * @param discount The discount record to add
     * @return bool True if successfully added
     */
    bool add(const shared_ptr<Discount>& discount) override;

    /**
     * @brief Update an existing discount record
     *
     * @param id The ID of the discount record to update
     * @param discount The updated discount record
     * @return bool True if successfully updated
     */
    bool updateById(int id, const shared_ptr<Discount>& discount) override;

    /**
     * @brief Delete a discount record by ID
     *
     * @param id The ID of the discount record to delete
     * @return bool True if successfully deleted
     */
    bool deleteById(int id) override;
};

#endif 