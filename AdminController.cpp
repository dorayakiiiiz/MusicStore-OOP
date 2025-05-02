#include "AdminController.h"
#include "AdminUI.h"
#include "AdminService.h"
#include "windows.h"
#include "utils.h"
#include "InputValidator.h"

// Implements the admin menu interface and all administrative operations
void AdminController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, 
                          vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {
    bool isValid;
    Error error;

    // Main admin menu loop
    while (1) {
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
                
                // Get details for new music item
                Music newItem = AdminUI::getNewMusicDetails();
                
                // Add the new item to inventory
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

                // Get ID of item to remove with validation
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
                if (AdminService::updateMusicItemPrice(items, id - 1, newPrice)) {
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

                // Display purchase history for each customer
                for (const auto& user : users) {
                    // Skip admin users
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
                if (AdminService::deleteUser(users, usernameToDelete)) {
                    printMessage("User deleted successfully!");
                    
                    // If admin deleted their own account, log them out
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
                
                // Generate sales statistics 
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