#include "AdminController.h"

#include <unordered_map>
#include <algorithm>
using std::unordered_map;

// edit file này

void AdminController::run(InventoryManager& inventory) {
    while (1) {

        displayMenu({
            "---------- MENU ADMIN ----------\n",
            "1. See music list",
            "2. Add new items",
            "3. Remove items",
            "4. Update price items",
            "5. View customer list",
            "6. View all customer purchase history",
            "7. Delete customer",
            "8. View sale statistics",
            "9. Log out\n"
        });


        int choice = stoi(getInput("Enter choice: "));
        switch (choice) {
            case 1: {
                vector<Music> allItems = inventory.getAllItems();
                cout << "---------- MUSIC LIST ----------\n";
                cout << "ID - Name - Artist - Genre - Price - Quantity\n";
                int idx = 1;
                for (int i = 0; i < allItems.size(); ++i) {
                    if (allItems[i].getQuantity() == 0) {
                        continue;
                    }  
                    cout << idx++ << ". ";allItems[i].displayItems();
                }
                cout << "-------------------------------\n";
                break;
            }
            case 2: {
                string name = getInput("Enter name: ");
                string artist = getInput("Enter artist: ");
                string genre = getInput("Enter genre: ");
                float price = stof(getInput("Enter price: "));
                int quantity = stoi(getInput("Enter quantity: "));

                Music item(name, artist, genre, price, quantity);

                inventory.addItem(item);

                cout << "\nAdd new items successfully!\n";
                
                break;
            } 
            case 3: {
                int id = stoi(getInput("Enter ID: "));
                
                bool success = inventory.removeItem(id);
                
                if (success) {
                    cout << "\nRemove items successfully!\n";
                } else {
                    cout << "\nInvalid ID!\n";
                }
                
                break;
            }
            case 4: {
                int id = stoi(getInput("Enter ID: "));
                float newPrice = stof(getInput("Enter new price: "));
                inventory.updateItemPrice(id - 1, newPrice);
                cout << "\nUpdate price successfully!\n";

                break;
            }
            case 5: {
                vector<shared_ptr<Customer>> allCustomers;
                Database::loadCustomers(allCustomers);
                cout << "---------- CUSTOMER LIST ----------\n";
                cout << "ID - Username - Password\n";
                for (int i = 0; i < allCustomers.size(); ++i) {
                    cout << i + 1 << ". " << allCustomers[i]->getUsername() << " - " << allCustomers[i]->getPassword() << "\n";
                }
                cout << "-----------------------------------\n";
                break;
            }
            case 6: {
                vector<shared_ptr<Customer>> allCustomers;
                Database::loadCustomers(allCustomers);
                if (allCustomers.empty()) {
                    cout << "No customers found.\n";
                    break;
                }
                vector<Order> allOrders;
                Database::loadOrder(allOrders);
                vector<Music> allItems = inventory.getAllItems(); 
                
                cout << "---------- CUSTOMER PURCHASE HISTORY ----------\n";
                for (const auto& customer : allCustomers) {
                    cout << "Customer: " << customer->getUsername() << "\n";
                    bool hasPurchase = false;
                    int idx = 1;
                    for (const auto& order : allOrders) {

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
                string usernameToDelete = getInput("Enter username to delete: ");
                vector<shared_ptr<Customer>> allCustomers;
                Database::loadCustomers(allCustomers);

                int indexToDelete = -1;
                for (int i = 0; i < allCustomers.size(); ++i) {
                    if (allCustomers[i]->getUsername() == usernameToDelete) {
                        indexToDelete = i;
                        break;
                    }
                }
            
                if (indexToDelete != -1) {
                    for (int i = indexToDelete; i < allCustomers.size() - 1; ++i) {
                        allCustomers[i] = allCustomers[i + 1];
                    }
                    allCustomers.pop_back(); 
            
                    Database::saveCustomers(allCustomers);
                    cout << "\nUser " << usernameToDelete << " deleted successfully.\n\n";
                } else {
                    cout << "\nUser not found.\n\n";
                }
                break;
            }
            case 8: {

                vector<Order> allOrders;
                Database::loadOrder(allOrders);
                vector<Music> allItems = inventory.getAllItems();

                unordered_map<string, pair<int, float>> itemStats;

                for (const auto& order : allOrders) {
                    const auto& purchasedItems = order.getPurchasedItems();
                    for (const auto& item : purchasedItems) {
                        itemStats[item.getName()].first += item.getQuantity();
                        itemStats[item.getName()].second += item.getPrice() * item.getQuantity();
                    }
                }
                // add the item that is not sold yet into itemStats
                for (const auto& item : allItems) {
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
                return;
            }
            default: 
            cout << "\nInvalid choice! Please try again!\n";
        }
    }
}