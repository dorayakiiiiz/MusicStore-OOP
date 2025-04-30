#include "AdminController.h"
#include "utils.h"
#include "MusicService.h"
#include "windows.h"

void AdminController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {

    while (1) {

        system("cls");
        printMessage("WELCOME ADMIN: " + currentUser->getUsername());
        AdminUI::displayMenu();

        int choice = stoi(getInput("Enter choice: "));

        switch (choice) {
            case 1: {
                system("cls");
                printHeader("MUSIC LIST");
                AdminUI::displayMusicList(items);
                printDashLine();

                system("pause");

                break;
            }
            case 2: {

                system("cls");
                printHeader("ADD NEW ITEMS");
                
                string name = getInput("Enter name: ");
                string artist = getInput("Enter artist: ");
                string genre = getInput("Enter genre: ");
                float price = stof(getInput("Enter price: "));
                int quantity = stoi(getInput("Enter quantity: "));

                Music item(name, artist, genre, price, quantity);

                MusicService::addMusicItem(items, item);

                printMessage("Add items successfully!");
                printDashLine();
                system("pause");

                break;
            } 
            case 3: {
                system("cls");
                printHeader("REMOVE ITEMS");

                AdminUI::displayMusicList(items);

                int id = stoi(getInput("Enter item's ID to remove: "));
                
                bool success = MusicService::removeMusicItem(items, id - 1);
                
                if (success) {
                    printMessage("Item removed successfully!");
                } else {
                    printMessage("Invalid ID! Item not found.");
                }
                printDashLine();
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                printHeader("UPDATE PRICE ITEMS");

                AdminUI::displayMusicList(items);

                int id = stoi(getInput("\nEnter item's ID: "));
                float newPrice = stof(getInput("Enter new price: "));

                MusicService::updateMusicItemPrice(items, id - 1, newPrice);

                printMessage("Price updated successfully!");
                printDashLine();

                system("pause");
                break;
            }
            case 5: {
                system("cls");
                printHeader("USER LIST");

                AdminUI::displayUserList(users);
                printDashLine();

                system("pause");
                break;
            }
            case 6: {
                system("cls");
                printHeader("CUSTOMER PURCHASE HISTORY");

                for (const auto& customer : users) {
                    if (customer->getRole() == "Admin") {
                        continue;
                    }

                    printMessage("Customer: " + customer->getUsername());   
                    bool hasPurchase = false;
                    int idx = 1;

                    for (const auto& order : orders) {
                        if (order.getUsername() == customer->getUsername()) {
                            hasPurchase = true;
                            
                            AdminUI::displayPurchasedHistory(order, idx++);

                            printDashLine();                  
                        
                        }
                    }
                    if (!hasPurchase) {
                        printMessage("No purchase history found for this customer.");
                    }
                    printDashLine();                
                }
                system("pause"); 
                break;
            }
            case 7: {
                system("cls");
                printHeader("DELETE USER");
                
                AdminUI::displayUserList(users);

                string del = getInput("\nEnter username to delete: ");

                int indexToDelete = -1;
                for (int i = 0; i < users.size(); ++i) {
                    if (users[i]->getUsername() == del) {
                        indexToDelete = i;
                        break;
                    }
                }
                // will move to UserService after refactoring
                if (indexToDelete != -1) {
                    users.erase(users.begin() + indexToDelete);
                    printMessage("User deleted successfully!");
                    if (currentUser->getUsername() == del) {
                        printMessage("You have deleted yourself! Please login again!");
                        currentUser = nullptr;
                        return;
                    }
                } else {
                    printMessage("User not found!");
                }
                printDashLine();
                system("pause");
                break;
            }
            case 8: {
                system("cls");
                unordered_map<string, pair<int, float>> itemStats;

                for (const auto& order : orders) {
                    const auto& purchasedItems = order.getPurchasedItems();
                    for (const auto& item : purchasedItems) {
                        itemStats[item.getName()].first += item.getQuantity();
                        itemStats[item.getName()].second += item.getPrice() * item.getQuantity();
                    }
                }
                // add the item that is not sold yet into itemStats
                for (const auto& item : items) {
                    if (item.getQuantity() > 0 && itemStats.find(item.getName()) == itemStats.end()) {
                        itemStats[item.getName()] = {0, 0};
                    }
                }

                // sort the itemStats by revenue
                vector<pair<string, pair<int, float>>> sortedItemStats(itemStats.begin(), itemStats.end());
                sort(sortedItemStats.begin(), sortedItemStats.end(), [](const auto& a, const auto& b) {
                    return a.second.second > b.second.second;
                });
                
                printHeader("SALE STATISTICS");

                AdminUI::displaySaleStatistics(sortedItemStats);
                printDashLine();
                system("pause");
                break;
            }
            case 9: {
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