#ifndef _READDATA_H_
#define _READDATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Discount.h"

using std::vector, std::string, std::ifstream, std::stringstream;

template <typename T>
class IReadData {
public:
    virtual vector<T> readData(const string&) const = 0;
    virtual ~IReadData() = default;
};

class ReadMusic : public IReadData<Music> {
public:
    vector<Music> readData(const string&) const override;
};

class ReadUser : public IReadData<shared_ptr<IUser>> {
public:
    vector<shared_ptr<IUser>> readData(const string&) const override;
};

class ReadOrder : public IReadData<Order> {
public:
    vector<Order> readData(const string&) const override;
};

class ReadDiscount : public IReadData<shared_ptr<IDiscount>> {
public:
    vector<shared_ptr<IDiscount>> readData(const string&) const override;
};
#endif