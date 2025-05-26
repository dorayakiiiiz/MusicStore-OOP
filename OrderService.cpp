#include "OrderService.h"
#include "IDataProvider.h"
#include "SQLDao.h"
#include <unordered_map>
#include <algorithm>

using std::unordered_map;

// Constructor
OrderService::OrderService(shared_ptr<IDataProvider> provider) {
    this->dataProvider = provider;
}

// Get the singleton instance of OrderService
shared_ptr<OrderService> OrderService::getInstance(shared_ptr<IDataProvider> provider) {
    if (instance == nullptr) {
        // If no provider is passed, use the default SqlDao
        if (!provider) {
            provider = make_shared<SqlDao>();
        }
        instance = shared_ptr<OrderService>(new OrderService(provider));
    }
    return instance;
}

// Get all orders from the repository
vector<Order> OrderService::getAllOrders() {
    return dataProvider->order()->getAll();
}

// Process order checkout and create a new order
void OrderService::checkout( const string& username, Cart& cart, float total) {
    // Create a new order with current cart items and total
    Order order(username, cart.getItems(), total);

    // Save the order to the repository
    dataProvider->order()->add(order);
    
    
    // Clear the cart after successful checkout
    cart.clear();
}

// Delete an order from the repository
void OrderService::deleteOrder(const string& username) {
    // Get all orders
    auto orders = dataProvider->order()->getAll();
    // Find and delete the order for the specified user
    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].getUsername() == username) {
            orders.erase(orders.begin() + i);
            i--;
        }
    }
}

// Retrieve orders for a specific user
vector<Order> OrderService::getUserOrders(const string& username) {
    // Get all orders from the repository
    auto orders = dataProvider->order()->getAll();

    vector<Order> userOrders;

    // Filter orders by username
    for (const auto& order : orders) {
        if (order.getUsername() == username) {
            userOrders.push_back(order);
        }
    }
    
    return userOrders;
}
