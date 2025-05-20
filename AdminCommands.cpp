#include "AdminCommands.h"
#include "AdminUI.h"
#include "Music.h"
#include "User.h"
#include "SalesRecord.h"
#include "MusicService.h"
#include "UserService.h"
#include "OrderService.h"
#include "SalesRecordService.h"
#include "utils.h"
#include "InputValidator.h"
#include "Registry.h"
#include "ConsoleUI.h"
#include <memory>
#include <conio.h>

using std::vector, std::string, std::shared_ptr, std::make_shared, std::tie, std::pair;

// ViewMusicListCommand implementation
std::string ViewMusicListCommand::getName() const {
    return "SEE MUSIC LIST";
}

bool ViewMusicListCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);
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
    return "ADD NEW ITEMS";
}

bool AddNewItemsCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30); 
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
    return "REMOVE ITEMS";
}

bool RemoveItemsCommand::execute() {
    bool isValid;
    Error error;

    clearScreen();
    printFrame(0, 0, 120, 30); 
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
    return "UPDATE PRICE";
}

bool UpdatePriceCommand::execute() {
    bool isValid;
    Error error;

    clearScreen();
    printFrame(0, 0, 120, 30); 
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
    return "VIEW USERS";
}

bool ViewUsersCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30); 
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
    return "VIEW PURCHASE HISTORY";
}

bool ViewAllPurchaseHistoriesCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30); 
    string header = "PURCHASE HISTORY";
    printHeader(header, (120 - header.length()*2) / 2 - 30, 1);

    // get all users from the repository
    vector<shared_ptr<User>> users = Registry::getSingleton<UserService>()->getAllUsers();

    // print the list of customers
    vector<shared_ptr<User>> customer = Registry::getSingleton<UserService>()->getAllCustomers();
    AdminUI::displayUserList(customer);

    int id;
    bool isValid;
    Error error;
    do {
        tie(isValid, id, error) = InputValidator::validateInt("Enter customer ID: ", 1, customer.size());
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);

    // Get the selected customer
    shared_ptr<User> selectedCustomer = customer[id - 1];
    printMessage("Customer: " + selectedCustomer->getUsername());

    vector<Order> userOrders = Registry::getSingleton<OrderService>()->getUserOrders(selectedCustomer->getUsername());
    if (userOrders.empty()) {
        printMessage("No purchase history found for this customer.");
    } else {
        for (int i = 0; i < userOrders.size(); ++i) {
            AdminUI::displayPurchasedHistory(userOrders[i], i + 1);
        }
    }
    
    pauseScreen();
    return true;
}

// DeleteUserCommand implementation
DeleteUserCommand::DeleteUserCommand(shared_ptr<User>& user) : currentUser(user) {}

std::string DeleteUserCommand::getName() const {
    return "DELETE USERS";
}

bool DeleteUserCommand::execute() {
    bool isValid;
    Error error;

    vector<shared_ptr<User>> users = Registry::getSingleton<UserService>()->getAllUsers();

    clearScreen();
    printFrame(0, 0, 120, 30);

    string header = "DELETE USERS";
    printHeader(header, (120 - header.length()*2) / 2 - 20, 2);

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

        // delete the order history of the deleted user
        Registry::getSingleton<OrderService>()->deleteOrder(delUser->getUsername());

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
    return "VIEW SALES STATISTICS";
}

bool ViewSalesStatisticsCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);
    string header = "SALE STATISTICS";
    printHeader(header, (120 - header.length()*2) / 2 - 30, 1);

    vector<SalesRecord> salesRecords = Registry::getSingleton<SalesRecordService>()->getAllSalesRecords();
    float totalRevenue = Registry::getSingleton<SalesRecordService>()->getTotalRevenue();

    AdminUI::displaySaleStatistics(salesRecords, totalRevenue);
    printDashLine();
    pauseScreen();
    return true;
}

// AdminLogoutCommand implementation
AdminLogoutCommand::AdminLogoutCommand(shared_ptr<User>& user) : currentUser(user) {}

std::string AdminLogoutCommand::getName() const {
    return "LOG OUT";
}

bool AdminLogoutCommand::execute() {
    printMessage("Log out successfully!");
    currentUser = nullptr;
    sleepScreen();
    return false; // Exit menu loop
}

