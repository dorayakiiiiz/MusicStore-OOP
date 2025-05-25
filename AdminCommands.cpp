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
#include "InputChecker.h"
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
    string header = "musicList";
    printHeader(header, (120 - header.length()*2) / 2 - 19, 1);

    vector<Music> items = MusicService::getInstance()->getAllMusic();
    if (items.empty()) {
        printFrame(30, 14, 60, 3); 
        printMessage("NO ITEMS FOUND!", 50, 15);
        printRepeatMessage(2, 1, "EXIT");

        char repeat = _getch();

        if (27 == repeat) {
            return true;
        }
    }

    AdminUI::displayMusicList(items, 8);
    return true;
}

// AddNewItemsCommand implementation
std::string AddNewItemsCommand::getName() const {
    return "ADD NEW ITEMS";
}

bool AddNewItemsCommand::execute() {
    while (true) {
        clearScreen();
        printFrame(0, 0, 120, 30); 
        string header = "addNewItems";
        printHeader(header, (120 - header.length()*2) / 2 - 26, 1);

        Music newItem = AdminUI::getNewMusicDetails();
        
        // Add the new item to inventory
        bool success = MusicService::getInstance()->addMusicItem(newItem);
        if (success) {
            printFrame(30, 22, 60, 3); 
            printMessage("ITEM ADDED SUCCESSFULLY!", 47, 23);
        } else {
            printFrame(30, 22, 60, 3); 
            printMessage("Item already exists!", 50, 23);
        }

        printRepeatMessage(2, 1, "EXIT");
        printRepeatMessage(107, 1, "CONTINUE");

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
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

    while (true) {
        clearScreen();
        printFrame(0, 0, 120, 30); 
        string header = "removeItems";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1);

        // Get all items from the repository
        vector<Music> items = MusicService::getInstance()->getAllMusic();
        AdminUI::displayMusicList(items, 7);

        int id = getValidatedInput<int>(
            "Enter item ID to remove: ",
            [&items](const string& prompt) {
                return InputChecker::validateInt(prompt, 10, 26, 1, items.size());
            },
            10, 26
        );
        
        // Remove the selected item
        bool success = MusicService::getInstance()->removeMusicItem(id);
        if (success) {
            printMessage("Item removed successfully!", 10, 27);
        } else {
            printMessage("Error while removing the items!", 10, 27);
        }

        items = MusicService::getInstance()->getAllMusic();
        if (items.empty()) {
            printMessage("No items left in inventory!", 10, 15);
        }

        printRepeatMessage(2, 1, "EXIT");
        printRepeatMessage(110, 1, "DELETE");

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
        else if (13 == repeat){
            continue;
        }
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

    while (true) {
        clearScreen();
        printFrame(0, 0, 120, 30); 
        string header = "updatePrice";
        printHeader(header, (120 - header.length()*2) / 2 - 22, 1);

        vector<Music> items = MusicService::getInstance()->getAllMusic();
        AdminUI::displayMusicList(items, 6);

        // Get ID of item to update with validation
        int id = getValidatedInput<int>(
            "Enter item ID to update: ",
            [&items](const string& prompt) {
                return InputChecker::validateInt(prompt, 10, 25, 1, items.size());
            },
            10, 25
        );

        // Get new price with validation
        float newPrice = getValidatedInput<float>(
            "Enter new price: ",
            [](const string& prompt) {
                return InputChecker::validateFloat(prompt, 10, 26, 0.0f);
            },
            10, 26
        );

        // Update the item's price
        bool success = MusicService::getInstance()->updateMusicItemPrice(id, newPrice);
        if (success) {
            printMessage("Price updated successfully!", 10, 27);
        } else {
            printMessage("Error while updating price!", 10, 27);
        }

        printRepeatMessage(2, 1, "EXIT");

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
    }
    return true;
}

// ViewUsersCommand implementation
std::string ViewUsersCommand::getName() const {
    return "VIEW USERS";
}

bool ViewUsersCommand::execute() {
    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30); 
        string header = "userList";
        printHeader(header, (120 - header.length()*2) / 2 - 18, 1);

        vector<shared_ptr<User>> users = UserService::getInstance()->getAllUsers();
        if (users.empty()) {
            printMessage("No users found!", 10, 15);
            printRepeatMessage(2, 1, "EXIT");

            char repeat = _getch();
            if (27 == repeat) {
                return true;
            }
            return true;
        }

        AdminUI::displayUserList(users);
        printRepeatMessage(2, 1, "EXIT");

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
    }
    return true;
}

// ViewAllPurchaseHistoriesCommand implementation (renamed from ViewPurchaseHistoryCommand)
std::string ViewAllPurchaseHistoriesCommand::getName() const {
    return "VIEW USER PURCHASE HISTORY";
}

bool ViewAllPurchaseHistoriesCommand::execute() {
    // get all users from the repository
    vector<shared_ptr<User>> users = UserService::getInstance()->getAllUsers();

    // print the list of customers
    vector<shared_ptr<User>> customer = UserService::getInstance()->getAllCustomers();

    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30); 
        string header = "purchaseHistory";
        printHeader(header, (120 - header.length()*2) / 2 - 31, 1);
        AdminUI::displayUserList(customer);

        int id = getValidatedInput<int>(
            "Enter customer ID to view purchase history: ",
            [&customer](const string& prompt_input) {
                return InputChecker::validateInt(prompt_input, 10, 24, 1, customer.size());
            },
            10, 24
        );

        // Get the selected customer
        shared_ptr<User> selectedCustomer = customer[id - 1];
        printMessage("Customer: " + selectedCustomer->getUsername(), 10, 15);

        vector<Order> userOrders = OrderService::getInstance()->getUserOrders(selectedCustomer->getUsername());
        if (userOrders.empty()) {
            printMessage("No purchase history found for this customer.", 10, 16);
        } else {
            for (int i = 0; i < userOrders.size(); ++i) {
                ConsoleUI::gotoXY(10, 17);
                AdminUI::displayPurchasedHistory(userOrders[i], i + 1);
            }
        }

        printRepeatMessage(108, 1, "CONTINUE");
        printRepeatMessage(2, 1, "EXIT");
        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
    }
    return true;
}

// DeleteUserCommand implementation
DeleteUserCommand::DeleteUserCommand(shared_ptr<User>& user) : currentUser(user) {}

std::string DeleteUserCommand::getName() const {
    return "DELETE USERS";
}

bool DeleteUserCommand::execute() {

    vector<shared_ptr<User>> users = UserService::getInstance()->getAllUsers();

    if (users.empty()) {
        printMessage("No users found!", 10, 15);
        printRepeatMessage(2, 1, "EXIT");

        char repeat = _getch();
        if (27 == repeat) {
            return true;
        }
    }
    
    while (true) {
        clearScreen();
        printFrame(0, 0, 120, 30);
        string header = "deleteUsers";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1);
        AdminUI::displayUserList(users);
        
        // Get username to delete
        int id = getValidatedInput<int>(
            "Enter user ID to delete: ",
            [&users](const string& prompt_input) {
                return InputChecker::validateInt(prompt_input, 10, 25, 1, users.size());
            },
            10, 25
        );

        // Check if admin is deleting their own account
        shared_ptr<User> delUser = UserService::getInstance()->getUserById(id);

        bool isCurrentUser = (currentUser->getUsername() == delUser->getUsername());
        
        // Delete the selected user
        bool success = UserService::getInstance()->deleteUserById(id);
        if (success) {
            printMessage("User deleted successfully!", 10, 26);

            // If admin deleted their own account, log them out
            if (isCurrentUser) {
                printMessage("You have deleted yourself. Logging out...", 10, 27);
                currentUser = nullptr;
                sleepScreen();
                return false; // Exit menu loop
            }
        } else {
            printMessage("User not found!", 10, 26);
        }

        // delete the order history of the deleted user
        OrderService::getInstance()->deleteOrder(delUser->getUsername());

        users = UserService::getInstance()->getAllUsers();
        if (users.empty()) {
            printMessage("No users left in the system!", 10, 27);
            printRepeatMessage(2, 1, "EXIT");

            char repeat = _getch();
            if (27 == repeat) {
                return true;
            }
            break;
        }

        printRepeatMessage(108, 1, "CONTINUE");
        printRepeatMessage(2, 1, "EXIT");

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
    }
    return true;
}

// ViewSalesStatisticsCommand implementation
std::string ViewSalesStatisticsCommand::getName() const {
    return "VIEW SALES STATISTICS";
}

bool ViewSalesStatisticsCommand::execute() {
    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30);
        string header = "saleStatistics";
        printHeader(header, (120 - header.length()*2) / 2 - 27, 1);

        vector<SalesRecord> salesRecords = SalesRecordService::getInstance()->getAllSalesRecords();
        float totalRevenue = SalesRecordService::getInstance()->getTotalRevenue();

        AdminUI::displaySaleStatistics(salesRecords, totalRevenue);
        printRepeatMessage(108, 1, "CONTINUE");
        printRepeatMessage(2, 1, "EXIT");

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
    }
    return true;
}

// AdminLogoutCommand implementation
AdminLogoutCommand::AdminLogoutCommand(shared_ptr<User>& user) : currentUser(user) {}

std::string AdminLogoutCommand::getName() const {
    return "LOG OUT";
}

bool AdminLogoutCommand::execute() {
    printMessage("Log out successfully!", 10, 25);
    currentUser = nullptr;
    sleepScreen();
    return false; // Exit menu loop
}

