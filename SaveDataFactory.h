#ifndef _SAVEDATAFACTORY_H_
#define _SAVEDATAFACTORY_H_

#include "SaveData.h"

template <typename T>
class SaveDataFactory;

template <>
class SaveDataFactory<Music> {
public:
    static shared_ptr<ISaveData<Music>> createSaveData() {
        return make_shared<SaveMusic>();
    }
};

template <>
class SaveDataFactory<shared_ptr<IUser>> {
public:
    static shared_ptr<ISaveData<shared_ptr<IUser>>> createSaveData() {
        return make_shared<SaveUser>();
    }
};

template <>
class SaveDataFactory<Order> {
public:
    static shared_ptr<ISaveData<Order>> createSaveData() {
        return make_shared<SaveOrder>();
    }
};

template <>
class SaveDataFactory<shared_ptr<IDiscount>> {
public:
    static shared_ptr<ISaveData<shared_ptr<IDiscount>>> createSaveData() {
        return make_shared<SaveDiscount>();
    }
};

#endif