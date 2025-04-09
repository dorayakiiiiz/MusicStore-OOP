#include "AdminMenu.h"

void AdminMenu::run(InventoryManager& inventory) {
    while (1) {
        UI::displayMenu({
            "---------- MENU ADMIN ----------\n\n",
            "1. Add new items",
            "2. Remove items",
            "3. Update price items",
            "4. Log out"
        });

        int choice = stoi(UI::getInput("Input choice: "));
        switch (choice) {
            case 1: {
                int id = stoi(UI::getInput("Input ID: "));
                string name = UI::getInput("Input name: ");
                string artist = UI::getInput("Input artist: ");
                string genre = UI::getInput("Input genre: ");
                float price = stof(UI::getInput("Input price: "));
                int quantity = stoi(UI::getInput("Input quantity: "));

                MusicItem item(id, name, artist, genre, price, quantity);

                inventory.addItem(item);

                cout << "Add new items successfully!\n";
                
                break;
            } 
            case 2: {
                int id = stoi(UI::getInput("Input ID: "));
                
                inventory.removeItem(id);
                
                cout << "Remove items successfully!\n";
                
                break;
            }
            case 3: {
                int id = stoi(UI::getInput("Input ID: "));
                float newPrice = stof(UI::getInput("Input new price: "));
                inventory.updateItemPrice(id, newPrice);

                cout << "Update price successfully!\n";

                break;
            }
            case 4: {
                return;
            }
            default: 
            cout << "Invalid choice! Please try again!\n";
        }
    }
}