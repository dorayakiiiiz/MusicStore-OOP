#include "AdminService.h"
#include <algorithm>

bool AdminService::addMusicItem(vector<Music>& items, const Music& item) {
    for (const auto& i : items) {
        if (i == item) {
            return false; 
        }
    }
    items.push_back(item);
    return true;
}

bool AdminService::removeMusicItem(vector<Music>& items, int id) {
    if (id < 0 || id >= items.size()) {
        return false;
    }
    items.erase(items.begin() + id);
    return true;
}

bool AdminService::updateMusicItemPrice(vector<Music>& items, int id, float price) {
    if (id < 0 || id >= items.size()) {
        return false;
    }
    items[id].updatePrice(price);
    return true;
}

bool AdminService::deleteUser(vector<shared_ptr<IUser>>& users, const string& username) {
    int index = findUserByUsername(users, username);
    if (index != -1) {
        users.erase(users.begin() + index);
        return true;
    }
    return false;
}

int AdminService::findUserByUsername(const vector<shared_ptr<IUser>>& users, const string& username) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return i;
        }
    }
    return -1;
}

// Statistics generation
vector<pair<string, pair<int, float>>> AdminService::generateSalesStatistics(
    const vector<Order>& orders, const vector<Music>& items) {
    
    unordered_map<string, pair<int, float>> itemStats;

    // Calculate sales and revenue for each item
    for (const auto& order : orders) {
        const auto& purchasedItems = order.getPurchasedItems();
        for (const auto& item : purchasedItems) {
            itemStats[item.getName()].first += item.getQuantity();
            itemStats[item.getName()].second += item.getPrice() * item.getQuantity();
        }
    }
    
    // Add items that haven't been sold yet
    for (const auto& item : items) {
        if (item.getQuantity() > 0 && itemStats.find(item.getName()) == itemStats.end()) {
            itemStats[item.getName()] = {0, 0};
        }
    }

    // Sort by revenue (highest first)
    vector<pair<string, pair<int, float>>> sortedItemStats(itemStats.begin(), itemStats.end());
    std::sort(sortedItemStats.begin(), sortedItemStats.end(), [](const auto& a, const auto& b) {
        return a.second.second > b.second.second;
    });
    
    return sortedItemStats;
}

vector<Order> AdminService::getUserPurchaseHistory(const vector<Order>& orders, const string& username) {
    vector<Order> userOrders;
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}