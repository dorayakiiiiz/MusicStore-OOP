#include "AdminController.h"
#include "AdminUI.h"
#include "AdminService.h"
#include "windows.h"
#include "utils.h"

void AdminController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, 
                          vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {
    bool isValid;
    Error error;


    while (1) {
        clearScreen();
        AdminUI::displayWelcomeMessage(currentUser->getUsername());
        AdminUI::displayMenu();

        int choice;
        do {
            std::tie(isValid, choice, error) = getIntInput("Enter your choice: ", 1, 9);
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);

        switch (choice) {
            case 1: { // See Music List
                clearScreen();
                printHeader("MUSIC LIST");
                AdminUI::displayMusicList(items);
                printDashLine();
                pauseScreen();
                break;
            }
            case 2: { // Add New Items
                clearScreen();
                printHeader("ADD NEW ITEMS");
                
                Music newItem = AdminUI::getNewMusicDetails();
                if (AdminService::addMusicItem(items, newItem)) {
                    printMessage("Item added successfully!");
                } else {
                    printMessage("Item already exists!");
                }
                
                printDashLine();
                pauseScreen();
                break;
            } 
            case 3: { // Remove Items
                clearScreen();
                printHeader("REMOVE ITEMS");
                AdminUI::displayMusicList(items);

                int id;
                do {
                    std::tie(isValid, id, error) = getIntInput("Enter item ID: ", 1, items.size());
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);
                
                if (AdminService::removeMusicItem(items, id - 1)) {
                    printMessage("Item removed successfully!");
                } else {
                    printMessage("Invalid ID! Item not found.");
                }
                printDashLine();
                pauseScreen();
                break;
            }
            case 4: { // Update Price Items
                clearScreen();
                printHeader("UPDATE PRICE ITEMS");
                AdminUI::displayMusicList(items);

                int id;
                do {
                    std::tie(isValid, id, error) = getIntInput("Enter item ID: ", 1, items.size());
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                float newPrice;
                do {
                    std::tie(isValid, newPrice, error) = getFloatInput("Enter new price: ", 0.0f);
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                if (AdminService::updateMusicItemPrice(items, id, newPrice)) {
                    printMessage("Price updated successfully!");
                } else {
                    printMessage("Invalid item ID!");
                }
                printDashLine();
                pauseScreen();
                break;
            }
            case 5: { // View Users List
                clearScreen();
                printHeader("USER LIST");
                AdminUI::displayUserList(users);
                printDashLine();
                pauseScreen();
                break;
            }
            case 6: { // View All Customers Purchase History
                clearScreen();
                printHeader("CUSTOMER PURCHASE HISTORY");

                for (const auto& user : users) {
                    if (user->getRole() == "Admin") {
                        continue;
                    }

                    printMessage("Customer: " + user->getUsername());   
                    vector<Order> userOrders = AdminService::getUserPurchaseHistory(orders, user->getUsername());
                    
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
                break;
            }
            case 7: { // Delete Customers
                clearScreen();
                printHeader("DELETE USER");
                AdminUI::displayUserList(users);

                string usernameToDelete;
                do {
                    std::tie(isValid, usernameToDelete, error) = getStringInput("Enter username to delete: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                bool isCurrentUser = (currentUser->getUsername() == usernameToDelete);
                
                if (AdminService::deleteUser(users, usernameToDelete)) {
                    printMessage("User deleted successfully!");
                    
                    if (isCurrentUser) {
                        printMessage("You have deleted yourself! Please login again!");
                        currentUser = nullptr;
                        Sleep(1000);
                        return;
                    }
                } else {
                    printMessage("User not found!");
                }
                
                printDashLine();
                pauseScreen();
                break;
            }
            case 8: { // View Sales Statistics
                clearScreen();
                printHeader("SALE STATISTICS");
                
                // Generate sales statistics using AdminService
                vector<pair<string, pair<int, float>>> salesStats = 
                    AdminService::generateSalesStatistics(orders, items);
                
                AdminUI::displaySaleStatistics(salesStats);
                printDashLine();
                pauseScreen();
                break;
            }
            case 9: { // Logout
                printMessage("Log out successfully!");
                currentUser = nullptr;
                Sleep(1000);
                return;
            }
            default: 
                printMessage("Invalid choice! Please try again.");
                Sleep(1000);
        }
    }
}