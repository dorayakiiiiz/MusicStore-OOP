#include "AdminCommands.h"
#include "../ui/AdminUI.h"
#include "../models/Music.h"
#include "../models/User.h"
#include "../models/SalesRecord.h"
#include "../services/MusicService.h"
#include "../services/UserService.h"
#include "../services/OrderService.h"
#include "../services/SalesRecordService.h"
#include "../ui/utils.h"
#include "../ui/InputChecker.h"
#include "../ui/ConsoleUI.h"
#include <memory>
#include <conio.h>

using std::vector, std::string, std::shared_ptr, std::make_shared, std::tie, std::pair;

// ViewMusicListCommand implementation
std::string ViewMusicListCommand::getName() const {
    return "SEE MUSIC LIST";
}

bool ViewMusicListCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30, AQUA);
    string header = "musicList";
    printHeader(header, (120 - header.length()*2) / 2 - 19, 1, LBLUE);

    vector<Music> items = MusicService::getInstance()->getAllMusic();

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
        printFrame(0, 0, 120, 30, AQUA); 
        string header = "addNewItems";
        printHeader(header, (120 - header.length()*2) / 2 - 26, 1, LBLUE);

        Music newItem = AdminUI::getNewMusicDetails();
        
        // Add the new item to inventory
        bool success = MusicService::getInstance()->addMusicItem(newItem);
        if (success) {
            printFrame(30, 22, 60, 3, LGREEN); 
            printMessage("ITEM ADDED SUCCESSFULLY!", 47, 23, LGREEN);
        } else {
            printFrame(30, 22, 60, 3, LRED); 
            printMessage("ITEM ALREADY EXISTS!", 50, 23, LRED);
        }

        printRepeatMessage(2, 1, "EXIT", LRED);
        printRepeatMessage(107, 1, "CONTINUE", YELLOW);

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
        printFrame(0, 0, 120, 30, AQUA); 
        string header = "removeItems";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1, LBLUE);

        // Get all items from the repository
        vector<Music> items = MusicService::getInstance()->getAllMusic();
        if (items.empty()) {
            printFrame(40, 14, 40, 3, LRED); 
            printMessage("NO ITEMS LEFT IN INVENTORY!", 45, 15, LRED);
            sleepScreen(1200);
            return true;
        }

        AdminUI::displayMusicList(items, 7);

        printFrameOptions(7, 25, 40, 1);
        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(9, 26);
        cout << "ENTER ITEM ID TO REMOVE  : ";
        ConsoleUI::setColor(WHITE);

        int id = getValidatedInput<int>(
            "ENTER ITEM ID TO REMOVE: ",
            [&items](const string& prompt) {
                return InputChecker::checkInt(prompt, 9, 26, 1, items.size());
            },
            9, 26
        );
        
        // Remove the selected item
        bool success = MusicService::getInstance()->removeMusicItem(id);
        if (success) {
            printFrame(49, 25, 40, 3, LGREEN); 
            printMessage("ITEM REMOVED SUCCESSFULLY!", 55, 26, LGREEN);
        } else {
            printFrame(49, 25, 40, 3, LRED); 
            printMessage("ERROR WHILE REMOVING THE ITEMS!", 50, 26, LRED);
        }

        printRepeatMessage(2, 1, "EXIT", LRED);
        printRepeatMessage(107, 1, "CONTINUE", YELLOW);

        char repeat = _getch();
        if (27 == repeat) {
            break;
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
        printFrame(0, 0, 120, 30, AQUA); 
        string header = "updatePrice";
        printHeader(header, (120 - header.length()*2) / 2 - 22, 1, LBLUE);

        vector<Music> items = MusicService::getInstance()->getAllMusic();
        if (items.empty()) {
            printFrame(40, 14, 40, 3, LRED); 
            printMessage("NO ITEMS LEFT IN INVENTORY!", 45, 15, LRED);
            sleepScreen(1200);
            return true;
        }
        AdminUI::displayMusicList(items, 6);

        printFrameOptions(7, 23, 40, 2);
        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(9, 24);
        cout << "ENTER ITEM ID TO UPDATE  : ";
        ConsoleUI::gotoXY(9, 26);
        cout << "ENTER NEW PRICE          : ";
        ConsoleUI::setColor(WHITE);

        // Get ID of item to update with validation
        int id = getValidatedInput<int>(
            "ENTER ITEM ID TO UPDATE: ",
            [&items](const string& prompt) {
                return InputChecker::checkInt(prompt, 9, 24, 1, items.size());
            },
            9, 24
        );

        // Get new price with validation
        float newPrice = getValidatedInput<float>(
            "ENTER NEW PRICE        : ",
            [](const string& prompt) {
                return InputChecker::checkFloat(prompt, 9, 26, 0.0f);
            },
            9, 26
        );

        // Update the item's price
        bool success = MusicService::getInstance()->updateMusicItemPrice(id, newPrice);
        if (success) {
            printFrame(49, 24, 40, 3, LGREEN); 
            printMessage("PRICE UPDATED SUCCESSFULLY!", 54, 25, LGREEN);
        } else {
            printFrame(49, 24, 40, 3, LRED); 
            printMessage("ERROR WHILE UPDATING PRICE!", 54, 25, LRED);
        }

        printRepeatMessage(2, 1, "EXIT", LRED);
        printRepeatMessage(107, 1, "CONTINUE", YELLOW);

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
    clearScreen();
    printFrame(0, 0, 120, 30, AQUA); 
    string header = "userList";
    printHeader(header, (120 - header.length()*2) / 2 - 18, 1, LBLUE);

    vector<shared_ptr<User>> users = UserService::getInstance()->getAllUsers();
    if (users.empty()) {
        printFrame(30, 14, 60, 3, LRED); 
        printMessage("NO USERS FOUND!", 50, 15, LRED);
        sleepScreen(1200);
        return true;
    }

    AdminUI::displayUserList(users, 8);
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
        printFrame(0, 0, 120, 30, AQUA); 
        string header = "purchaseHistory";
        printHeader(header, (120 - header.length()*2) / 2 - 34, 1, LBLUE);
        AdminUI::displayUserList(customer, 6);

        printFrameOptions(20, 24, 60, 1);
        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(22, 25);
        cout << "ENTER CUSTOMER ID TO VIEW PURCHASE HISTORY  : ";
        ConsoleUI::setColor(WHITE);

        int id = getValidatedInput<int>(
            "ENTER CUSTOMER ID TO VIEW PURCHASE HISTORY: ",
            [&customer](const string& prompt_input) {
                return InputChecker::checkInt(prompt_input, 22, 25, 1, customer.size());
            },
            22, 25
        );

        clearScreen();
        printFrame(0, 0, 120, 30, AQUA); 
        printHeader(header, (120 - header.length()*2) / 2 - 34, 1, LBLUE);

        // Get the selected customer
        shared_ptr<User> selectedCustomer = customer[id - 1];
        printFrame(30, 7, 60, 3, AQUA);
        printMessage("CUSTOMER: " + selectedCustomer->getUsername(), 50, 8, YELLOW);

        vector<Order> userOrders = OrderService::getInstance()->getUserOrders(selectedCustomer->getUsername());

        AdminUI::displayPurchasedHistory(userOrders);

        printRepeatMessage(107, 1, "CONTINUE", YELLOW);
        printRepeatMessage(2, 1, "EXIT", LRED);
        char repeat = _getch();
        if (27 == repeat) {
            return true;
        }
    }
    return true;
}

// DeleteUserCommand implementation
DeleteUserCommand::DeleteUserCommand(shared_ptr<User>& user) : _currentUser(user) {}

std::string DeleteUserCommand::getName() const {
    return "DELETE USERS";
}

bool DeleteUserCommand::execute() {
    
    while (true) {
        clearScreen();
        printFrame(0, 0, 120, 30, AQUA);
        string header = "deleteUsers";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1, LBLUE);
        vector<shared_ptr<User>> users = UserService::getInstance()->getAllUsers();

        if (users.empty()) {
            printFrame(30, 14, 60, 3, LRED);
            printMessage("NO USERS LEFT IN THE SYSTEM!", 50, 15, LRED);
            sleepScreen(1200);
            return true;
        }

        AdminUI::displayUserList(users, 7);
        
        printFrameOptions(20, 25, 40, 1);
        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(22, 26);
        cout << "ENTER USER ID TO DELETE  : ";
        ConsoleUI::setColor(WHITE);

        // Get username to delete
        int id = getValidatedInput<int>(
            "ENTER USER ID TO DELETE: ",
            [&users](const string& prompt_input) {
                return InputChecker::checkInt(prompt_input, 22, 26, 1, users.size());
            },
            22, 26
        );

        // Check if admin is deleting their own account
        shared_ptr<User> delUser = UserService::getInstance()->getUserById(id);

        bool isCurrentUser = (_currentUser->getUsername() == delUser->getUsername());
        
        // Delete the selected user
        bool success = UserService::getInstance()->deleteUserById(id);
        if (success) {
            printFrame(62, 25, 38, 3, LGREEN); 
            printMessage("USER DELETED SUCCESSFULLY!", 67, 26, LGREEN);

            // If admin deleted their own account, log them out
            if (isCurrentUser) {
                printFrame(30, 13, 60, 5, LRED);
                printMessage("YOU HAVE DELETED YOURSELF. LOGGING OUT...", 45, 15, LRED);
                _currentUser = nullptr;
                sleepScreen(1200);
                return false; // Exit menu loop
            }
        } else {
            printFrame(42, 25, 38, 3, LRED); 
            printMessage("USER NOT FOUND!", 55, 26, LRED);
        }

        // delete the order history of the deleted user
        OrderService::getInstance()->deleteOrder(delUser->getUsername());

        printRepeatMessage(107, 1, "CONTINUE", YELLOW);
        printRepeatMessage(2, 1, "EXIT", LRED);

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
    clearScreen();
    printFrame(0, 0, 120, 30, AQUA);
    string header = "saleStatistics";
    printHeader(header, (120 - header.length()*2) / 2 - 27, 1, LBLUE);

    vector<SalesRecord> salesRecords = SalesRecordService::getInstance()->getAllSalesRecords();
    float totalRevenue = SalesRecordService::getInstance()->getTotalRevenue();

    AdminUI::displaySaleStatistics(salesRecords, totalRevenue);
    return true;
}

// AdminLogoutCommand implementation
AdminLogoutCommand::AdminLogoutCommand(shared_ptr<User>& user) : _currentUser(user) {}

std::string AdminLogoutCommand::getName() const {
    return "LOG OUT";
}

bool AdminLogoutCommand::execute() {
    printFrame(5, 24, 60, 5, LGREEN);
    printMessage("LOG OUT SUCCESSFULLY!", 23, 26, LGREEN);
    _currentUser = nullptr;
    sleepScreen(1200);
    return false; // Exit menu loop
}