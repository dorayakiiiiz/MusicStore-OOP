/**
 * @file ReadDataFactory.h
 * @brief Header file for the ReadDataFactory class
 * 
 * @details Defines a factory for creating appropriate data readers
 *          based on the data type being loaded
 */

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
 * @return shared_ptr<IReadData<shared_ptr<User>>> Pointer to a User reader
 */
template <>
inline shared_ptr<IReadData<shared_ptr<User>>> ReadDataFactory<shared_ptr<User>>::createReadData() {
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
inline shared_ptr<IReadData<shared_ptr<Discount>>> ReadDataFactory<shared_ptr<Discount>>::createReadData() {
    return make_shared<ReadDiscount>();
}

#endif