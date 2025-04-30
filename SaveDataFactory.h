#ifndef _SAVEDATAFACTORY_H_
#define _SAVEDATAFACTORY_H_

#include "SaveData.h"

template <typename T>
class SaveDataFactory {
public:
    static shared_ptr<ISaveData<T>> createSaveData();
};

// or if u dont want to use inline, just move the implementation to a .cpp file

template <>
inline shared_ptr<ISaveData<Music>> SaveDataFactory<Music>::createSaveData() {
    return make_shared<SaveMusic>();
}

template <>
inline shared_ptr<ISaveData<shared_ptr<IUser>>> SaveDataFactory<shared_ptr<IUser>>::createSaveData() {
    return make_shared<SaveUser>();
}

template <>
inline shared_ptr<ISaveData<Order>> SaveDataFactory<Order>::createSaveData() {
    return make_shared<SaveOrder>();
}

template <>
inline shared_ptr<ISaveData<shared_ptr<IDiscount>>> SaveDataFactory<shared_ptr<IDiscount>>::createSaveData() {
    return make_shared<SaveDiscount>();
}

#endif