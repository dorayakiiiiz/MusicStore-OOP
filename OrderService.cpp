#include "OrderService.h"

#include <unordered_map>
#include <algorithm>

using std::unordered_map;

// Process order checkout and create a new order
void OrderService::checkout(vector<Order>& orders, const string& username, Cart& cart, float total) {
    // Create a new order with current cart items and total
    Order order(username, cart.getItems(), total);
    // Add to orders collection
    orders.push_back(order);
    // Clear the cart after successful checkout
    cart.clear();
}

// Retrieve orders for a specific user
vector<Order> OrderService::getUserOrders(const vector<Order>& orders, const string& username) {
    vector<Order> userOrders;
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}

// Generate sales statistics for all music items
vector<pair<string, pair<int, float>>> OrderService::generateSalesStatistics(
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
vector<Order> OrderService::getUserPurchaseHistory(const vector<Order>& orders, const string& username) {
    vector<Order> userOrders;
    // Iterate through all orders and filter by username
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}