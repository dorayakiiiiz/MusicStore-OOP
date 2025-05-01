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

class AdminService {
public:
    // Music inventory management (direct implementation, no delegation)
    static bool addMusicItem(vector<Music>& items, const Music& item);
    static bool removeMusicItem(vector<Music>& items, int id);
    static bool updateMusicItemPrice(vector<Music>& items, int id, float price);
    
    // User management (direct implementation)
    static bool deleteUser(vector<shared_ptr<IUser>>& users, const string& username);
    static int findUserByUsername(const vector<shared_ptr<IUser>>& users, const string& username);
    
    // Sales statistics
    static vector<pair<string, pair<int, float>>> generateSalesStatistics(
        const vector<Order>& orders, const vector<Music>& items);
        
    // Get user purchase history
    static vector<Order> getUserPurchaseHistory(const vector<Order>& orders, const string& username);
};

#endif