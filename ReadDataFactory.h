#ifndef _READDATAFACTORY_H_
#define _READDATAFACTORY_H_

#include "ReadData.h"

/**
 * @brief Factory class for creating data reader objects
 * @tparam T Type of data to read
 */
template <typename T>
class ReadDataFactory {
public:
    /**
     * @brief Create a reader object for the specified type
     * @return shared_ptr<IReadData<T>> Pointer to a reader for the specified type
     */
    static shared_ptr<IReadData<T>> createReadData();
};

/**
 * @brief Specialization for Music data
 * @return shared_ptr<IReadData<Music>> Pointer to a Music reader
 */
template <>
inline shared_ptr<IReadData<Music>> ReadDataFactory<Music>::createReadData() {
    return make_shared<ReadMusic>();
}

/**
 * @brief Specialization for User data
 * @return shared_ptr<IReadData<shared_ptr<IUser>>> Pointer to a User reader
 */
template <>
inline shared_ptr<IReadData<shared_ptr<IUser>>> ReadDataFactory<shared_ptr<IUser>>::createReadData() {
    return make_shared<ReadUser>();
}

/**
 * @brief Specialization for Order data
 * @return shared_ptr<IReadData<Order>> Pointer to an Order reader
 */
template <>
inline shared_ptr<IReadData<Order>> ReadDataFactory<Order>::createReadData() {
    return make_shared<ReadOrder>();
}

/**
 * @brief Specialization for Discount data
 * @return shared_ptr<IReadData<shared_ptr<IDiscount>>> Pointer to a Discount reader
 */
template <>
inline shared_ptr<IReadData<shared_ptr<IDiscount>>> ReadDataFactory<shared_ptr<IDiscount>>::createReadData() {
    return make_shared<ReadDiscount>();
}

#endif