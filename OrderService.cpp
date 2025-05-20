#include "OrderService.h"
#include "Registry.h"
#include "IOrderRepository.h"
#include <unordered_map>
#include <algorithm>

using std::unordered_map;

// Get all orders from the repository
vector<Order> OrderService::getAllOrders() {
    return Registry::getSingleton<IOrderRepository>()->getAll();
}

// Process order checkout and create a new order
void OrderService::checkout( const string& username, Cart& cart, float total) {
    // Create a new order with current cart items and total
    Order order(username, cart.getItems(), total);
    // Add to orders collection in the repository
    bool success = Registry::getSingleton<IOrderRepository>()->add(order);
    // Clear the cart after successful checkout
    cart.clear();
}

// Delete an order from the repository
void OrderService::deleteOrder(const string& username) {
    // Get all orders
    auto orders = Registry::getSingleton<IOrderRepository>()->getAll();
    // Find and delete the order for the specified user
    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].getUsername() == username) {
            orders.erase(orders.begin() + i);
            Registry::getSingleton<IOrderRepository>()->deleteById(i + 1);
            i--;
        }
    }
}

// Retrieve orders for a specific user
vector<Order> OrderService::getUserOrders(const string& username) {
    // Get all orders from the repository
    auto orders = Registry::getSingleton<IOrderRepository>()->getAll();

    vector<Order> userOrders;

    // Filter orders by username
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    
    return userOrders;
}
