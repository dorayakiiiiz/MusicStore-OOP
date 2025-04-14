#include "AdminController.h"

#include <unordered_map>
using std::unordered_map;

// edit file này

void AdminController::run(InventoryManager& inventory) {
    while (1) {
        UI::displayMenu({
            "---------- MENU ADMIN ----------\n",
            "1. Add new items",
            "2. Remove items",
            "3. Update price items",
            "4. View all customer purchase history",
            "5. Delete customer",
            "6. View sale statistics",
            "7. Log out\n"
        });

        int choice = stoi(UI::getInput("Enter choice: "));
        switch (choice) {
            case 1: {
                int id = stoi(UI::getInput("Enter ID: "));
                string name = UI::getInput("Enter name: ");
                string artist = UI::getInput("Enter artist: ");
                string genre = UI::getInput("Enter genre: ");
                float price = stof(UI::getInput("Enter price: "));
                int quantity = stoi(UI::getInput("Enter quantity: "));

                MusicItem item(id, name, artist, genre, price, quantity);

                inventory.addItem(item);

                cout << "\nAdd new items successfully!\n";
                
                break;
            } 
            case 2: {
                int id = stoi(UI::getInput("Enter ID: "));
                
                bool success = inventory.removeItem(id);
                
                if (success) {
                    cout << "\nRemove items successfully!\n";
                } else {
                    cout << "\nInvalid ID!\n";
                }
                
                break;
            }
            case 3: {
                int id = stoi(UI::getInput("Enter ID: "));
                float newPrice = stof(UI::getInput("Enter new price: "));
                inventory.updateItemPrice(id, newPrice);

                cout << "\nUpdate price successfully!\n";

                break;
            }
            case 4: {
                vector<shared_ptr<Customer>> allCustomers;
                Database::getInstance()->loadCustomers(allCustomers);
                vector<Order> allOrders;
                Database::getInstance()->loadOrder(allOrders);
                vector<MusicItem> allItems = inventory.getAllItems(); 
                
                cout << "---------- CUSTOMER PURCHASE HISTORY ----------\n";
                for (const auto& customer : allCustomers) {
                    cout << "Customer: " << customer->getUsername() << "\n";
                    bool hasPurchase = false;
                    
                    for (const auto& order : allOrders) {
                        if (order.getUsername() == customer->getUsername()) {
                            hasPurchase = true;
                            cout << "Order ID: " << order.getOrderId() << '\n';
                            cout << "Items purchased:\n";

                            const auto& purchasedItems = order.getPurchasedItems();
                            for (const auto& [itemID, quantity] : purchasedItems) {
                                string itemName;
                                float itemPrice = 0;
                                for (const auto& item : allItems) {
                                    if (item.getID() == itemID) {
                                        itemName = item.getName();
                                        itemPrice = item.getPrice();
                                        break;
                                    }
                                }
                                cout << "- " << itemName << " - Quantity: " << quantity
                                     << " - Price per unit: $" << itemPrice
                                     << " - Total: $" << itemPrice * quantity << '\n';
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
            case 5: {
                string usernameToDelete = UI::getInput("Enter username to delete: ");
                vector<shared_ptr<Customer>> allCustomers;
                Database::getInstance()->loadCustomers(allCustomers);

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
            
                    Database::getInstance()->saveCustomers(allCustomers);
                    cout << "\nUser " << usernameToDelete << " deleted successfully.\n\n";
                } else {
                    cout << "\nUser not found.\n\n";
                }
                break;
            }
            case 6: {
                vector<Order> allOrders;
                Database::getInstance()->loadOrder(allOrders);
                vector<MusicItem> allItems = inventory.getAllItems();

                unordered_map<int, pair<int, float>> productStats;
                for (const auto& order : allOrders) {
                    const auto& items = order.getPurchasedItems();
                    for (const auto& [itemId, quantity] : items) {
                        float price = 0;
                        for (const auto& item : allItems) {
                            if (item.getID() == itemId) {
                                price = item.getPrice();
                                break;
                            }
                        }
                        productStats[itemId].first += quantity;
                        productStats[itemId].second += price * quantity;
                    }  
                }
                
                cout << "---------- SALES STATISTICS ----------\n\n";
                float totalRevenue = 0;
                for (const auto& [id, stats] : productStats) {
                    string productName;
                    for (const auto& item : allItems) {
                        if (item.getID() == id) {
                            productName = item.getName();
                        }
                    }
                    cout << "Product: " << productName << " - Sold : "
                    << stats.first << " - Revenue: $" << stats.second << "\n";
                    totalRevenue += stats.second;
                }

                cout << "------------------------------\n";
                cout << "TOTAL REVENUE: $" << totalRevenue << "\n\n";
                break;
            }
            case 7: {
                return;
            }
            default: 
            cout << "\nInvalid choice! Please try again!\n";
        }
    }
}