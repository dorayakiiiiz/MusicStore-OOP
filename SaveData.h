#ifndef _SAVEDATA_H_
#define _SAVEDATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Discount.h"
#include "DatabaseConnector.h"
#include <memory>   

using std::vector, std::string, std::ofstream, std::stringstream, std::shared_ptr;

/**
 * @brief Interface for saving data to files
 * @tparam T Type of data to save
 */
template <typename T>
class ISaveData {
public:
    /**
     * @brief Save data to a file
     * 
     * @param filename Path to the file to save data to
     * @param data List of data items to save
     */
    virtual void saveData(const vector<T>&) const = 0;
    
    /**
     * @brief Virtual destructor
     */
    virtual ~ISaveData() = default;
};

/**
 * @brief Class for saving music data to files
 */
class SaveMusic : public ISaveData<Music> {
public:
    /**
     * @brief Save music data to a file
     * 
     * @param filename Path to the file to save data to
     * @param items List of music items to save
     */
    void saveData(const vector<Music>&) const override;
};

/**
 * @brief Class for saving user data to files
 */
class SaveUser : public ISaveData<shared_ptr<IUser>> {
public:
    /**
     * @brief Save user data to a file
     * 
     * @param filename Path to the file to save data to
     * @param users List of users to save
     */
    void saveData(const vector<shared_ptr<IUser>>&) const override;
};

/**
 * @brief Class for saving order data to files
 */
class SaveOrder : public ISaveData<Order> {
public:
    /**
     * @brief Save order data to a file
     * 
     * @param filename Path to the file to save data to
     * @param orders List of orders to save
     */
    void saveData(const vector<Order>&) const override;
};

/**
 * @brief Class for saving discount voucher data to files
 */
class SaveDiscount : public ISaveData<shared_ptr<Discount>> {
public:
    /**
     * @brief Save discount voucher data to a file
     * 
     * @param filename Path to the file to save data to
     * @param vouchers List of discount vouchers to save
     */
    void saveData(const vector<shared_ptr<Discount>>&) const override;
    // hehe
};
#endif