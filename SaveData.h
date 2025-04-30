#ifndef _SAVEDATA_H_
#define _SAVEDATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Discount.h"

using std::vector, std::string, std::ofstream, std::stringstream;

template <typename T>
class ISaveData {
public:
    virtual void saveData(const string&, const vector<T>&) const = 0;
    virtual ~ISaveData() = default;
};

class SaveMusic : public ISaveData<Music> {
public:
    void saveData(const string&, const vector<Music>&) const override;
};

class SaveUser : public ISaveData<shared_ptr<IUser>> {
public:
    void saveData(const string&, const vector<shared_ptr<IUser>>&) const override;
};

class SaveOrder : public ISaveData<Order> {
public:
    void saveData(const string&, const vector<Order>&) const override;
};

class SaveDiscount : public ISaveData<shared_ptr<IDiscount>> {
public:
    void saveData(const string&, const vector<shared_ptr<IDiscount>>&) const override;
};
#endif