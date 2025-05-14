/**
 * @file AdminController.cpp
 * @brief Implementation file for the AdminController class 
 * 
 * @details Contains implementations of admin operations including managing music inventory,
 * user management, and generating sales reports.
 */

#include "AdminController.h"
#include "AdminUI.h"
#include "MusicService.h"
#include "UserService.h"
#include "OrderService.h"
#include "windows.h"
#include "utils.h"
#include "InputValidator.h"
#include "ServiceLocator.h"

// Constructor for AdminController
AdminController::AdminController() {}


    // Implements the admin menu interface and all administrative operations
void AdminController::menu(vector<Music>& items, vector<shared_ptr<User>>& users, vector<Order>& orders, 
                          vector<shared_ptr<Discount>>& vouchers, shared_ptr<User>& currentUser) {
    bool isValid;
    Error error;

    // Main admin menu loop
    while (true) {
        clearScreen();
        AdminUI::displayWelcomeMessage(currentUser->getUsername());
        AdminUI::displayMenu();

        // Get admin choice with validation
        int choice;
        do {
            std::tie(isValid, choice, error) = InputValidator::validateInt("Enter your choice: ", 1, 9);
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);

        switch (choice) {
            case AdminOption::ADMIN_MUSIC_LIST: // See Music List
                handleMusicList(items);
                break;

            case AdminOption::ADD_NEW_ITEMS: // Add New Items
                handleAddNewItems(items);
                break;

            case AdminOption::REMOVE_ITEMS: // Remove Items
                handleRemoveItems(items);
                break;

            case AdminOption::UPDATE_PRICE: // Update Price Items
                handleUpdatePrice(items);
                break;

            case AdminOption::VIEW_USERS: // View Users List
                handleViewUsers(users);
                break;

            case AdminOption::VIEW_PURCHASE_HISTORY: // View All Customers Purchase History
                handleViewPurchaseHistory(users, orders);
                break;

            case AdminOption::DELETE_CUSTOMERS: { // Delete Customers
                if (handleDeleteCustomers(users, currentUser)) {
                    return; // Admin deleted themselves, so exit
                }
                break;
            }

            case AdminOption::VIEW_SALES_STATISTICS: // View Sales Statistics
                handleViewSalesStatistics(orders, items);
                break;

            case AdminOption::ADMIN_LOGOUT: // Logout
                handleLogout(currentUser);
                return;
            
            default: 
                printMessage("Invalid choice! Please try again.");
                Sleep(1000);
        }
    }
}


// handle the first case of the menu: display music list
void AdminController::handleMusicList(vector<Music>& items) {
    clearScreen();
    printHeader("MUSIC LIST");
    AdminUI::displayMusicList(items);
    printDashLine();
    pauseScreen();
}

// handle the second case of the menu: add new items
void AdminController::handleAddNewItems(vector<Music>& items) {
    auto musicService = ServiceLocator::getSingleton<MusicService>();
    while (1) {
        clearScreen();
        printHeader("ADD NEW ITEMS");

        Music newItem = AdminUI::getNewMusicDetails();
        
        // Add the new item to inventory
        bool success = musicService->addMusicItem(items, newItem);
        if (success) {
            printMessage("Item added successfully!");
        } else {
            printMessage("Item already exists!");
        }

        printDashLine();
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }

}

// handle the third case of the menu: remove items
void AdminController::handleRemoveItems(vector<Music>& items) {
    bool isValid;
    Error error;

    auto musicService = ServiceLocator::getSingleton<MusicService>();
    while (1) {
        clearScreen();
        printHeader("REMOVE ITEMS");
        AdminUI::displayMusicList(items);
        int id;
        do {
            std::tie(isValid, id, error) = InputValidator::validateInt("Enter item ID: ", 1, items.size());
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);
        
        // Remove the selected item
        bool success = musicService->removeMusicItem(items, id - 1);
        if (success) {
            printMessage("Item removed successfully!");
        } else {
            printMessage("Invalid ID! Item not found.");
        }

        printDashLine();
        if (items.empty()) {
            printMessage("No items left in inventory!");
            pauseScreen();
            break;
        }
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }

    // Get ID of item to remove with validation

}

// handle the fourth case of the menu: update price
void AdminController::handleUpdatePrice(vector<Music>& items) {
    bool isValid;
    Error error;

    auto musicService = ServiceLocator::getSingleton<MusicService>();
    while (1) {
        clearScreen();
        printHeader("UPDATE PRICE ITEMS");
        AdminUI::displayMusicList(items);

        // Get ID of item to update with validation
        int id;
        do {
            std::tie(isValid, id, error) = InputValidator::validateInt("Enter item ID: ", 1, items.size());
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);

        // Get new price with validation
        float newPrice;
        do {
            std::tie(isValid, newPrice, error) = InputValidator::validateFloat("Enter new price: ", 0.0f);
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);

        // Update the item's price
        bool success = musicService->updateMusicItemPrice(items, id - 1, newPrice);
        if (success) {
            printMessage("Price updated successfully!");
        } else {
            printMessage("Invalid item ID!");
        }

        printDashLine();
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }
}

// handle the fifth case of the menu: view users list
void AdminController::handleViewUsers(vector<shared_ptr<User>>& users) {
    clearScreen();
    printHeader("USER LIST");
    AdminUI::displayUserList(users);
    printDashLine();
    pauseScreen();
}

// handle the sixth case of the menu: view all customers purchase history
void AdminController::handleViewPurchaseHistory(vector<shared_ptr<User>>& users, vector<Order>& orders) {
    clearScreen();
    printHeader("CUSTOMER PURCHASE HISTORY");

    auto orderService = ServiceLocator::getSingleton<OrderService>();
    // Display purchase history for each customer
    for (const auto& user : users) {
        // Skip admin users
        if (Role::ADMIN == user->getRole()) {
            continue;
        }

        printMessage("Customer: " + user->getUsername());   
        vector<Order> userOrders = orderService->getUserPurchaseHistory(orders, user->getUsername());
        
        if (userOrders.empty()) {
            printMessage("No purchase history found for this customer.");
        } else {
            int idx = 1;
            for (const auto& order : userOrders) {
                AdminUI::displayPurchasedHistory(order, idx++);
                printDashLine();
            }
        }
        printDashLine();                
    }
    
    pauseScreen();
}

// handle the seventh case of the menu: delete customers
bool AdminController::handleDeleteCustomers(vector<shared_ptr<User>>& users, shared_ptr<User>& currentUser) {
    bool isValid;
    Error error;

    auto userService = ServiceLocator::getSingleton<UserService>();
    clearScreen();
    printHeader("DELETE USER");
    if (users.empty()) {
        printMessage("No users found!");
        pauseScreen();
        return false;
    }
    while (1) {
        printMessage("User list:");

        AdminUI::displayUserList(users);
        // Get username to delete
        string usernameToDelete;
        do {
            std::tie(isValid, usernameToDelete, error) = InputValidator::validateString("Enter username to delete: ");
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);

        // Check if admin is deleting their own account
        bool isCurrentUser = (currentUser->getUsername() == usernameToDelete);
        
        // Delete the selected user
        bool success = userService->deleteUser(users, usernameToDelete);
        if (success) {
            printMessage("User deleted successfully!");
            
            // If admin deleted their own account, log them out
            if (isCurrentUser) {
                printMessage("You have deleted yourself! Please login again!");
                currentUser = nullptr;
                Sleep(1000);
                return true;
            }
        } else {
            printMessage("User not found!");
        }

        if (users.empty()) {
            printMessage("No users left in the system!");
            pauseScreen();
            break;
        }

        printDashLine();
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }
    return false;
}

// handle the eighth case of the menu: view sales statistics
void AdminController::handleViewSalesStatistics(vector<Order>& orders, vector<Music>& items) {
    clearScreen();
    printHeader("SALE STATISTICS");
    
    auto orderService = ServiceLocator::getSingleton<OrderService>();
    // Generate sales statistics 
    vector<pair<string, pair<int, float>>> salesStats = 
        orderService->generateSalesStatistics(orders, items);
    
    AdminUI::displaySaleStatistics(salesStats);
    printDashLine();
    pauseScreen();
}

// handle the ninth case of the menu: logout
void AdminController::handleLogout(shared_ptr<User>& currentUser) {
    printMessage("Log out successfully!");
    currentUser = nullptr;
    Sleep(1000);
}

