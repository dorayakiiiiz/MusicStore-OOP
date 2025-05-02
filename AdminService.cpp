#include "AdminService.h"
#include <algorithm>

// Add a new music item to the inventory
bool AdminService::addMusicItem(vector<Music>& items, const Music& item) {
    // Check if item already exists
    for (const auto& i : items) {
        if (i == item) {
            return false; 
        }
    }
    // Add the new item
    items.push_back(item);
    return true;
}

// Remove a music item from the inventory by ID
bool AdminService::removeMusicItem(vector<Music>& items, int id) {
    // Validate ID
    if (id < 0 || id >= items.size()) {
        return false;
    }
    // Remove the item
    items.erase(items.begin() + id);
    return true;
}

// Update the price of a music item by ID
bool AdminService::updateMusicItemPrice(vector<Music>& items, int id, float price) {
    // Validate ID
    if (id < 0 || id >= items.size()) {
        return false;
    }
    // Update the price
    items[id].updatePrice(price);
    return true;
}

// Delete a user account by username
bool AdminService::deleteUser(vector<shared_ptr<IUser>>& users, const string& username) {
    int index = findUserByUsername(users, username);
    if (index != -1) {
        users.erase(users.begin() + index);
        return true;
    }
    return false;
}

// Find a user by username, returns the index or -1 if not found
int AdminService::findUserByUsername(const vector<shared_ptr<IUser>>& users, const string& username) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return i;
        }
    }
    return -1;
}

// Generate sales statistics for all music items
vector<pair<string, pair<int, float>>> AdminService::generateSalesStatistics(
    const vector<Order>& orders, const vector<Music>& items) {
    
    // Map to store item stats: item name -> (quantity sold, revenue)
    unordered_map<string, pair<int, float>> itemStats;

    // Calculate sales and revenue for each item across all orders
    for (const auto& order : orders) {
        const auto& purchasedItems = order.getPurchasedItems();
        for (const auto& item : purchasedItems) {
            // Add quantity sold and revenue for this item
            itemStats[item.getName()].first += item.getQuantity();
            itemStats[item.getName()].second += item.getPrice() * item.getQuantity();
        }
    }
    
    // Add items that haven't been sold yet with 0 sales
    for (const auto& item : items) {
        if (item.getQuantity() > 0 && itemStats.find(item.getName()) == itemStats.end()) {
            itemStats[item.getName()] = {0, 0};
        }
    }

    // Convert map to vector and sort by revenue (highest first)
    vector<pair<string, pair<int, float>>> sortedItemStats(itemStats.begin(), itemStats.end());
    std::sort(sortedItemStats.begin(), sortedItemStats.end(), [](const auto& a, const auto& b) {
        return a.second.second > b.second.second;
    });
    
    return sortedItemStats;
}

// Get purchase history for a specific user
vector<Order> AdminService::getUserPurchaseHistory(const vector<Order>& orders, const string& username) {
    vector<Order> userOrders;
    // Iterate through all orders and filter by username
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}