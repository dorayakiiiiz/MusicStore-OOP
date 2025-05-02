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

// Service class for admin-related business logic
class AdminService {
public:
    // Add a new music item to the inventory
    // Returns true if successful, false if item already exists
    static bool addMusicItem(vector<Music>& items, const Music& item);
    
    // Remove a music item from the inventory by ID
    // Returns true if successful, false if invalid ID
    static bool removeMusicItem(vector<Music>& items, int id);
    
    // Update the price of a music item by ID
    // Returns true if successful, false if invalid ID
    static bool updateMusicItemPrice(vector<Music>& items, int id, float price);
    
    // Delete a user account by username
    // Returns true if successful, false if user not found
    static bool deleteUser(vector<shared_ptr<IUser>>& users, const string& username);
    
    // Find a user by username, returns the index or -1 if not found
    static int findUserByUsername(const vector<shared_ptr<IUser>>& users, const string& username);
    
    // Generate sales statistics for all music items
    // Returns a vector of pairs (item name, (quantity sold, total revenue))
    static vector<pair<string, pair<int, float>>> generateSalesStatistics(
        const vector<Order>& orders, const vector<Music>& items);
        
    // Get purchase history for a specific user
    // Returns a vector of orders made by the specified user
    static vector<Order> getUserPurchaseHistory(const vector<Order>& orders, const string& username);
};

#endif