#include "AdminController.h"
#include "utils.h"
#include "MusicService.h"

void AdminController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {

    while (1) {
        cout << "\n---------- WELCOME ADMIN: " << currentUser->getUsername() << " ----------\n\n";
        vector<string> options = {
            "---------- MENU ADMIN ----------\n",
            "1. See music list",
            "2. Add new items",
            "3. Remove items",
            "4. Update price items",
            "5. View users list",
            "6. View all customers purchased history",
            "7. Delete customers",
            "8. View sale statistics",
            "9. Log out\n"
        };

        displayMenu(options);

        int choice = stoi(getInput("Enter choice: "));
        switch (choice) {
            case 1: {
                cout << "---------- MUSIC LIST ----------\n";
                cout << "ID - Name - Artist - Genre - Price - Quantity\n";
                int idx = 1;
                for (int i = 0; i < items.size(); ++i) {
                    if (items[i].getQuantity() == 0) {
                        continue;
                    }  
                    cout << idx++ << ". ";
                    items[i].displayItems();
                }
                cout << "-------------------------------\n";
                break;
            }
            case 2: {
                cout << "\n---------- ADD NEW ITEMS ----------\n";
                string name = getInput("Enter name: ");
                string artist = getInput("Enter artist: ");
                string genre = getInput("Enter genre: ");
                float price = stof(getInput("Enter price: "));
                int quantity = stoi(getInput("Enter quantity: "));

                Music item(name, artist, genre, price, quantity);

                MusicService::addMusicItem(items, item);

                cout << "\nAdd new items successfully!\n";
                cout << "------------------------------------------\n";
                break;
            } 
            case 3: {
                cout << "\n---------- REMOVE ITEMS ----------\n";
                int id = stoi(getInput("Enter ID: "));
                
                bool success = MusicService::removeMusicItem(items, id - 1);
                
                if (success) {
                    cout << "\nRemove items successfully!\n";
                } else {
                    cout << "\nInvalid ID!\n";
                }
                cout << "------------------------------------------\n";
                break;
            }
            case 4: {
                cout << "\n---------- UPDATE PRICE ----------\n";
                int id = stoi(getInput("Enter ID: "));
                float newPrice = stof(getInput("Enter new price: "));

                MusicService::updateMusicItemPrice(items, id - 1, newPrice);

                cout << "\nUpdate price successfully!\n";
                cout << "------------------------------------------\n";
                break;
            }
            case 5: {
                cout << "---------- USER LIST ----------\n";
                cout << "ID - Username - Password - Role\n";
                for (int i = 0; i < users.size(); ++i) {
                    cout << i + 1 << ". ";
                    users[i]->displayInfo();
                }
                cout << "-----------------------------------\n";
                break;
            }
            case 6: {
                
                cout << "---------- CUSTOMER PURCHASE HISTORY ----------\n";
                for (const auto& customer : users) {
                    if (customer->getRole() == "Admin") {
                        continue;
                    }
                    cout << "Customer: " << customer->getUsername() << "\n";
                    bool hasPurchase = false;
                    int idx = 1;
                    for (const auto& order : orders) {

                        if (order.getUsername() == customer->getUsername()) {
                            hasPurchase = true;
                            cout << "Order " << idx++ << ":\n";
                            cout << "Items purchased:\n";

                            const auto& purchasedItems = order.getPurchasedItems();
                            for (const auto& item : purchasedItems) {
                                cout << "- " << item.getName() << " - Quantity: " << item.getQuantity()
                                     << " - Price per unit: $" << item.getPrice()
                                     << " - Total: $" << item.getPrice() * item.getQuantity() << '\n';
                            }
                            cout << "Order total: $" << order.getTotal() << '\n';
                            cout << "-----------------------------\n";
                        }
                    }
                    if (!hasPurchase) {
                        cout << "No purchase history.\n";
                    }
                    cout << "-----------------------------\n";
                }
                break;
            }
            case 7: {
                cout << "\n---------- DELETE CUSTOMER ----------\n";
                string del = getInput("Enter username of customer: ");

                int indexToDelete = -1;
                for (int i = 0; i < users.size(); ++i) {
                    if (users[i]->getUsername() == del && users[i]->getRole() == "Customer") {
                        indexToDelete = i;
                        break;
                    }
                }
            
                if (indexToDelete != -1) {
                    users.erase(users.begin() + indexToDelete);
                    cout << "\nCustomer " << del << " deleted successfully.\n\n";
                } else {
                    cout << "\nCustomer not found.\n\n";
                }
                cout << "-----------------------------------\n";
                break;
            }
            case 8: {

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
                
                cout << "---------- SALES STATISTICS ----------\n\n";
                float totalRevenue = 0;
                for (const auto& [name, stats] : sortedItemStats) {
                    cout << "Product: " << name << " - Sold : "
                    << stats.first << " - Revenue: $" << stats.second << "\n";
                    totalRevenue += stats.second;
                }

                cout << "------------------------------\n";
                cout << "TOTAL REVENUE: $" << totalRevenue << "\n\n";
                break;
            }
            case 9: {
                cout << "\nYou have logged out successfully!\n";
                currentUser = nullptr;
                return;
            }
            default: 
            cout << "\nInvalid choice! Please try again!\n";
        }
    }
}