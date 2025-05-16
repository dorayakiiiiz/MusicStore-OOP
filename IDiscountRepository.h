#ifndef _IDISCOUNT_REPOSITORY_H_
#define _IDISCOUNT_REPOSITORY_H_

#include "IRepository.h"
#include "Discount.h"

class IDiscountRepository : public IRepository<shared_ptr<Discount>> {
public:
    virtual ~IDiscountRepository() = default;

    /**
     * @brief Get all discount records
     *
     * @return std::vector<shared_ptr<Discount>> Collection of all discount records
     */
    virtual std::vector<shared_ptr<Discount>> getAll() = 0;

    /**
     * @brief Get a discount record by ID
     *
     * @param id The ID of the discount record
     * @return shared_ptr<Discount> The discount record
     */
    virtual shared_ptr<Discount> getById(int id) = 0;

    /**
     * @brief Add a new discount record
     *
     * @param discount The discount record to add
     * @return bool True if successfully added
     */
    virtual bool add(const shared_ptr<Discount>& discount) = 0;

    /**
     * @brief Update an existing discount record
     *
     * @param id The ID of the discount record to update
     * @param discount The updated discount record
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const shared_ptr<Discount>& discount) = 0;

    /**
     * @brief Delete a discount record by ID
     *
     * @param id The ID of the discount record to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;
};

#endif