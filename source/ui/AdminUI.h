/**
 * @file AdminUI.h
 * @brief Header file for the AdminUI class
 * 
 * @details Defines the AdminUI class which provides display functions and
 *          input collection methods for the administrator interface
 */

#ifndef _ADMIN_UI_H_
#define _ADMIN_UI_H_

#include <iostream>
#include <vector>
#include <utility>
#include "../models/Music.h"
#include "../models/User.h"
#include "../models/Order.h"
#include "../models/SalesRecord.h"
#include "../models/Discount.h"
#include <memory>
using std::shared_ptr, std::pair;

/**
 * @brief UI class for administrator interface
 * 
 * @details Provides methods for displaying admin-specific UI elements and collecting admin input
 */
class AdminUI {
public:
    /**
     * @brief Displays a welcome message for the admin
     * @param username The username of the admin
     */
    static void displayWelcomeMessage(const string& username);
    
    /**
     * @brief Displays a formatted list of all music items in inventory
     * @param items Vector containing all music items in inventory
     */
    static void displayMusicList(vector<Music>& items, int maxPerPage);
    
    /**
     * @brief Displays a formatted list of all registered users
     * @param users Vector containing all registered users
     */
    static void displayUserList(const vector<shared_ptr<User>>& users, int maxPerPage);
    
    /**
     * @brief Displays the details of a specific order
     * @param order The order object containing purchase information
     * @param id The order identifier
     */
    static void displayPurchasedHistory(vector<Order> order);
    
    /**
     * @brief Displays sales statistics for items sold in the store
     * @param itemStats Vector of pairs containing item name and sales statistics (quantity and revenue)
     */
    static void displaySaleStatistics(vector<SalesRecord> salesRecords, float totalRevenue);
    
    /**
     * @brief Collects information from the admin to create a new music item
     * @return A new Music object with the user-provided details
     */
    static Music getNewMusicDetails();

};

#endif