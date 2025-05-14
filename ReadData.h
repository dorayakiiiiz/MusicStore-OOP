/**
 * @file ReadData.h
 * @brief Header file for data reading classes
 * 
 * @details Defines interfaces and classes for loading different types of data
 *          from persistent storage into the application
 */

#ifndef _READDATA_H_
#define _READDATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Discount.h"
#include "Discount.h"
#include "DatabaseConnector.h"

using std::vector, std::string, std::ifstream, std::stringstream, std::make_shared, std::shared_ptr;   

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
    virtual vector<T> readData() const = 0;
    
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
    vector<Music> readData() const override;
};

/**
 * @brief Class for reading user data from files
 */
class ReadUser : public IReadData<shared_ptr<User>> {
public:
    /**
     * @brief Read user data from a file
     * 
     * @param filename Path to the file to read data from
     * @return vector<shared_ptr<User>> List of users read from the file
     */
    vector<shared_ptr<User>> readData() const override;
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
    vector<Order> readData() const override;
};

/**
 * @brief Class for reading discount voucher data from files
 */
class ReadDiscount : public IReadData<shared_ptr<Discount>> {
public:
    /**
     * @brief Read discount voucher data from a file
     * 
     * @param filename Path to the file to read data from
     * @return vector<shared_ptr<Discount>> List of discount vouchers read from the file
     */
    vector<shared_ptr<Discount>> readData() const override;
};


#endif