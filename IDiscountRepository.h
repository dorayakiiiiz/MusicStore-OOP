#ifndef _IDISCOUNT_REPOSITORY_H_
#define _IDISCOUNT_REPOSITORY_H_

#include "IRepository.h"
#include "Discount.h"

class IDiscountRepository : public IRepository<Discount> {
public:
    virtual ~IDiscountRepository() = default;

    /**
     * @brief Get all discount records
     *
     * @return std::vector<Discount> Collection of all discount records
     */
    virtual std::vector<Discount> getAll() = 0;

    /**
     * @brief Get a discount record by ID
     *
     * @param id The ID of the discount record
     * @return Discount The discount record
     */
    virtual Discount getById(int id) = 0;

    /**
     * @brief Add a new discount record
     *
     * @param discount The discount record to add
     * @return bool True if successfully added
     */
    virtual bool add(const Discount& discount) = 0;

    /**
     * @brief Update an existing discount record
     *
     * @param id The ID of the discount record to update
     * @param discount The updated discount record
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const Discount& discount) = 0;

    /**
     * @brief Delete a discount record by ID
     *
     * @param id The ID of the discount record to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;
};

#endif