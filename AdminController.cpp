#include "AdminController.h"

// edit file này

void AdminController::run(InventoryManager& inventory) {
    while (1) {
        UI::displayMenu({
            "---------- MENU ADMIN ----------\n\n",
            "1. Add new items",
            "2. Remove items",
            "3. Update price items",
            "4. View customer purchase history",
            "5. Log out"
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

                cout << "Add new items successfully!\n";
                
                break;
            } 
            case 2: {
                int id = stoi(UI::getInput("Enter ID: "));
                
                inventory.removeItem(id);
                
                cout << "Remove items successfully!\n";
                
                break;
            }
            case 3: {
                int id = stoi(UI::getInput("Enter ID: "));
                float newPrice = stof(UI::getInput("Enter new price: "));
                inventory.updateItemPrice(id, newPrice);

                cout << "Update price successfully!\n";

                break;
            }
            case 4: {

                string username = UI::getInput("Enter customer username: ");
                vector<Order> allOrders;
                Database::getInstance()->loadOrder(allOrders);

                cout << "Purchase history for " << username << ":\n";
                for (const auto& order : allOrders) {
                    if (order.getUsername() == username) {
                        cout << "Oder ID: " << order.getOrderId() << " - Total: " << order.getTotal() << '\n';
                    }
                }

                break;
            }
            case 5: {
                return;
            }
            default: 
            cout << "Invalid choice! Please try again!\n";
        }
    }
}