#ifndef _SAVEDATAFACTORY_H_
#define _SAVEDATAFACTORY_H_

#include "SaveData.h"

/**
 * @brief Factory class for creating data saver objects
 * @tparam T Type of data to save
 */
template <typename T>
class SaveDataFactory {
public:
    /**
     * @brief Create a saver object for the specified type
     * @return shared_ptr<ISaveData<T>> Pointer to a saver for the specified type
     */
    static shared_ptr<ISaveData<T>> createSaveData();
};

/**
 * @brief Specialization for Music data
 * @return shared_ptr<ISaveData<Music>> Pointer to a Music saver
 */
template <>
inline shared_ptr<ISaveData<Music>> SaveDataFactory<Music>::createSaveData() {
    return make_shared<SaveMusic>();
}

/**
 * @brief Specialization for User data
 * @return shared_ptr<ISaveData<shared_ptr<IUser>>> Pointer to a User saver
 */
template <>
inline shared_ptr<ISaveData<shared_ptr<IUser>>> SaveDataFactory<shared_ptr<IUser>>::createSaveData() {
    return make_shared<SaveUser>();
}

/**
 * @brief Specialization for Order data
 * @return shared_ptr<ISaveData<Order>> Pointer to an Order saver
 */
template <>
inline shared_ptr<ISaveData<Order>> SaveDataFactory<Order>::createSaveData() {
    return make_shared<SaveOrder>();
}

/**
 * @brief Specialization for Discount data
 * @return shared_ptr<ISaveData<shared_ptr<IDiscount>>> Pointer to a Discount saver
 */
template <>
inline shared_ptr<ISaveData<shared_ptr<IDiscount>>> SaveDataFactory<shared_ptr<IDiscount>>::createSaveData() {
    return make_shared<SaveDiscount>();
}

#endif