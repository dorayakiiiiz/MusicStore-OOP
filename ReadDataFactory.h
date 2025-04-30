#ifndef _READDATAFACTORY_H_
#define _READDATAFACTORY_H_

#include "ReadData.h"

template <typename T>
class ReadDataFactory {
public:
    static shared_ptr<IReadData<T>> createReadData();
};

template <>
inline shared_ptr<IReadData<Music>> ReadDataFactory<Music>::createReadData() {
    return make_shared<ReadMusic>();
}

template <>
inline shared_ptr<IReadData<shared_ptr<IUser>>> ReadDataFactory<shared_ptr<IUser>>::createReadData() {
    return make_shared<ReadUser>();
}

template <>
inline shared_ptr<IReadData<Order>> ReadDataFactory<Order>::createReadData() {
    return make_shared<ReadOrder>();
}

template <>
inline shared_ptr<IReadData<shared_ptr<IDiscount>>> ReadDataFactory<shared_ptr<IDiscount>>::createReadData() {
    return make_shared<ReadDiscount>();
}

// template <typename T>
// class ReadDataFactory {
// public:
//     static shared_ptr<IReadData<T>> createReadData(const string& type) {
//         if (type == "Music") {
//             return make_shared<ReadMusic>();
//         } else if (type == "User") {
//             return make_shared<ReadUser>();
//         } else if (type == "Order") {
//             return make_shared<ReadOrder>();
//         } else if (type == "Discount") {
//             return make_shared<ReadDiscount>();
//         } else {
//             throw std::invalid_argument("Invalid type for ReadDataFactory");
//         }
//     }

// };


#endif