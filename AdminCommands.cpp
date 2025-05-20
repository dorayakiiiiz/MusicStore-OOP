#include "AdminCommands.h"
#include "AdminUI.h"
#include "Music.h"
#include "User.h"
#include "MusicService.h"
#include "UserService.h"
#include "OrderService.h"
#include "utils.h"
#include "InputValidator.h"
#include "Registry.h"
#include "ConsoleUI.h"
#include <memory>
#include <conio.h>

using std::vector, std::string, std::shared_ptr, std::make_shared, std::tie, std::pair;

// ViewMusicListCommand implementation
std::string ViewMusicListCommand::getName() const {
    return "See music list";
}

bool ViewMusicListCommand::execute() {
    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30);
    string header = "MUSIC LIST";
    printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

    vector<Music> items = Registry::getSingleton<MusicService>()->getAllMusic();
    if (items.empty()) {
        printMessage("No items found!");
        pauseScreen();
        return true;
    }

    AdminUI::displayMusicList(items);
    printDashLine();
    pauseScreen();
    return true;
}

// AddNewItemsCommand implementation
std::string AddNewItemsCommand::getName() const {
    return "Add new items";
}

bool AddNewItemsCommand::execute() {
    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30); 
    while (true) {
        string header = "ADD NEW ITEMS";
        printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

        Music newItem = AdminUI::getNewMusicDetails();
        
        // Add the new item to inventory
        bool success = Registry::getSingleton<MusicService>()->addMusicItem(newItem);
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
    return true;
}

// RemoveItemsCommand implementation
std::string RemoveItemsCommand::getName() const {
    return "Remove items";
}

bool RemoveItemsCommand::execute() {
    bool isValid;
    Error error;

    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30); 
    while (true) {
        string header = "REMOVE ITEMS";
        printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

        // Get all items from the repository
        vector<Music> items = Registry::getSingleton<MusicService>()->getAllMusic();
        AdminUI::displayMusicList(items);

        int id;
        do {
            tie(isValid, id, error) = InputValidator::validateInt("Enter item ID: ", 1, items.size());
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);
        
        // Remove the selected item
        bool success = Registry::getSingleton<MusicService>()->removeMusicItem(id);
        if (success) {
            printMessage("Item removed successfully!");
        } else {
            printMessage("Error while removing the items!");
        }

        printDashLine();
        items = Registry::getSingleton<MusicService>()->getAllMusic();
        if (items.empty()) {
            printMessage("tNo items left in inventory!");
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
    return true;
}

// UpdatePriceCommand implementation
std::string UpdatePriceCommand::getName() const {
    return "Update price";
}

bool UpdatePriceCommand::execute() {
    bool isValid;
    Error error;

    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30); 
    while (true) {
        string header = "UPDATE PRICE";
        printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

        vector<Music> items = Registry::getSingleton<MusicService>()->getAllMusic();
        AdminUI::displayMusicList(items);

        // Get ID of item to update with validation
        int id;
        do {
            tie(isValid, id, error) = InputValidator::validateInt("Enter item ID: ", 1, items.size());
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        // Get new price with validation
        float newPrice;
        do {
            tie(isValid, newPrice, error) = InputValidator::validateFloat("Enter new price: ", 0.0f);
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        // Update the item's price
        bool success = Registry::getSingleton<MusicService>()->updateMusicItemPrice(id, newPrice);
        if (success) {
            printMessage("Price updated successfully!");
        } else {
            printMessage("Error while updating price!");
        }

        printDashLine();
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }
    return true;
}

// ViewUsersCommand implementation
std::string ViewUsersCommand::getName() const {
    return "View users";
}

bool ViewUsersCommand::execute() {
    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30); 
    string header = "USER LIST";
    printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

    vector<shared_ptr<User>> users = Registry::getSingleton<UserService>()->getAllUsers();
    if (users.empty()) {
        printMessage("No users found!");
        pauseScreen();
        return true;
    }

    AdminUI::displayUserList(users);
    printDashLine();
    pauseScreen();
    return true;
}

// ViewAllPurchaseHistoriesCommand implementation (renamed from ViewPurchaseHistoryCommand)
std::string ViewAllPurchaseHistoriesCommand::getName() const {
    return "View purchase history";
}

bool ViewAllPurchaseHistoriesCommand::execute() {
    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30); 
    string header = "PURCHASE HISTORY";
    printHeader(header, (120 - header.length()*2) / 2 - 30, 2);

    vector<shared_ptr<User>> users = Registry::getSingleton<UserService>()->getAllUsers();
    vector<Order> orders = Registry::getSingleton<OrderService>()->getAllOrders();

    // Display purchase history for each customer
    for (const auto& user : users) {
        // Skip admin users
        if (Role::ADMIN == user->getRole()) {
            continue;
        }

        printMessage("Customer: " + user->getUsername());
        vector<Order> userOrders = Registry::getSingleton<OrderService>()->getUserPurchaseHistory(orders, user->getUsername());
        
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
    return true;
}

// DeleteUserCommand implementation
DeleteUserCommand::DeleteUserCommand(shared_ptr<User>& user) : currentUser(user) {}

std::string DeleteUserCommand::getName() const {
    return "Delete users";
}

bool DeleteUserCommand::execute() {
    bool isValid;
    Error error;

    vector<shared_ptr<User>> users = Registry::getSingleton<UserService>()->getAllUsers();

    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30);

    string header = "DELETE USERS";
    printHeader(header, (120 - header.length()*2) / 2 - 30, 2);
    if (users.empty()) {
        printMessage("No users found!");
        pauseScreen();
        return true;
    }
    
    while (true) {
        printMessage("User list:");
        AdminUI::displayUserList(users);
        
        // Get username to delete
        int id;
        do {
            tie(isValid, id, error) = InputValidator::validateInt("Enter user's id to delete: ");
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        // Check if admin is deleting their own account
        shared_ptr<User> delUser = Registry::getSingleton<UserService>()->getUserById(id);
        bool isCurrentUser = (currentUser->getUsername() == delUser->getUsername());
        
        // Delete the selected user
        bool success = Registry::getSingleton<UserService>()->deleteUserById(id);
        if (success) {
            printMessage("User deleted successfully!");

            // If admin deleted their own account, log them out
            if (isCurrentUser) {
                printMessage("You have deleted yourself. Logging out...");
                currentUser = nullptr;
                sleepScreen();
                return false; // Exit menu loop
            }
        } else {
            printMessage("User not found!");
        }

        users = Registry::getSingleton<UserService>()->getAllUsers();
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
    return true;
}

// ViewSalesStatisticsCommand implementation
std::string ViewSalesStatisticsCommand::getName() const {
    return "View sales statistics";
}

bool ViewSalesStatisticsCommand::execute() {
    clearScreen();
    ConsoleUI::printFrame(0, 0, 120, 30);
    string header = "SALE STATISTICS";
    printHeader(header, (120 - header.length()*2) / 2 - 30, 1);
    
    vector<Music> items = Registry::getSingleton<MusicService>()->getAllMusic();
    vector<Order> orders = Registry::getSingleton<OrderService>()->getAllOrders();

    // Generate sales statistics 
    vector<pair<string, pair<int, float>>> salesStats = 
        Registry::getSingleton<OrderService>()->generateSalesStatistics(orders, items);
    
    AdminUI::displaySaleStatistics(salesStats);
    printDashLine();
    pauseScreen();
    return true;
}

// AdminLogoutCommand implementation
AdminLogoutCommand::AdminLogoutCommand(shared_ptr<User>& user) : currentUser(user) {}

std::string AdminLogoutCommand::getName() const {
    return "Log out";
}

bool AdminLogoutCommand::execute() {
    printMessage("Log out successfully!");
    currentUser = nullptr;
    sleepScreen();
    return false; // Exit menu loop
}

