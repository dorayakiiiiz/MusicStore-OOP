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

/**
 * @brief Interface for reading data from files
 * @tparam T Type of data to read
 */
template <typename T>
class IReadData {
public:
    /**
     * @brief Read data from a file
     * 
     * @param filename Path to the file to read data from
     * @return vector<T> List of data items read from the file
     */
    virtual vector<T> readData(const string&) const = 0;
    
    /**
     * @brief Virtual destructor
     */
    virtual ~IReadData() = default;
};

/**
 * @brief Class for reading music data from files
 */
class ReadMusic : public IReadData<Music> {
public:
    /**
     * @brief Read music data from a file
     * 
     * @param filename Path to the file to read data from
     * @return vector<Music> List of music items read from the file
     */
    vector<Music> readData(const string&) const override;
};

/**
 * @brief Class for reading user data from files
 */
class ReadUser : public IReadData<shared_ptr<IUser>> {
public:
    /**
     * @brief Read user data from a file
     * 
     * @param filename Path to the file to read data from
     * @return vector<shared_ptr<IUser>> List of users read from the file
     */
    vector<shared_ptr<IUser>> readData(const string&) const override;
};

/**
 * @brief Class for reading order data from files
 */
class ReadOrder : public IReadData<Order> {
public:
    /**
     * @brief Read order data from a file
     * 
     * @param filename Path to the file to read data from
     * @return vector<Order> List of orders read from the file
     */
    vector<Order> readData(const string&) const override;
};

/**
 * @brief Class for reading discount voucher data from files
 */
class ReadDiscount : public IReadData<shared_ptr<IDiscount>> {
public:
    /**
     * @brief Read discount voucher data from a file
     * 
     * @param filename Path to the file to read data from
     * @return vector<shared_ptr<IDiscount>> List of discount vouchers read from the file
     */
    vector<shared_ptr<IDiscount>> readData(const string&) const override;
};
#endif