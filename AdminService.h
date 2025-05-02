#ifndef _ADMIN_SERVICE_H_
#define _ADMIN_SERVICE_H_

#include "Order.h"
#include "Music.h"
#include "User.h"
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <memory>

using std::vector, std::string, std::pair, std::unordered_map, std::shared_ptr;

/**
 * @brief Service class for admin-related business logic
 */
class AdminService {
public:
    /**
     * @brief Add a new music item to the inventory
     * 
     * @param items Reference to the vector of music items
     * @param item The new music item to add
     * @return bool True if successful, false if item already exists
     */
    static bool addMusicItem(vector<Music>& items, const Music& item);
    
    /**
     * @brief Remove a music item from the inventory by ID
     * 
     * @param items Reference to the vector of music items
     * @param id Index of the item to remove
     * @return bool True if successful, false if invalid ID
     */
    static bool removeMusicItem(vector<Music>& items, int id);
    
    /**
     * @brief Update the price of a music item by ID
     * 
     * @param items Reference to the vector of music items
     * @param id Index of the item to update
     * @param price New price for the item
     * @return bool True if successful, false if invalid ID
     */
    static bool updateMusicItemPrice(vector<Music>& items, int id, float price);
    
    /**
     * @brief Delete a user account by username
     * 
     * @param users Reference to the vector of user accounts
     * @param username Username of the account to delete
     * @return bool True if successful, false if user not found
     */
    static bool deleteUser(vector<shared_ptr<IUser>>& users, const string& username);
    
    /**
     * @brief Find a user by username
     * 
     * @param users Vector of user accounts to search in
     * @param username Username to search for
     * @return int Index of the found user or -1 if not found
     */
    static int findUserByUsername(const vector<shared_ptr<IUser>>& users, const string& username);
    
    /**
     * @brief Generate sales statistics for all music items
     * 
     * @param orders Vector of all orders to analyze
     * @param items Vector of all music items in inventory
     * @return vector<pair<string, pair<int, float>>> Vector of pairs mapping item names to their sales stats (quantity sold, revenue)
     */
    static vector<pair<string, pair<int, float>>> generateSalesStatistics(
        const vector<Order>& orders, const vector<Music>& items);
        
    /**
     * @brief Get purchase history for a specific user
     * 
     * @param orders Vector of all orders to search in
     * @param username Username to get history for
     * @return vector<Order> Vector of orders made by the specified user
     */
    static vector<Order> getUserPurchaseHistory(const vector<Order>& orders, const string& username);
};

#endif