#include "CustomerMenu.h"
#include "DiscountFactory.h"


void CustomerMenu::run(InventoryManager& inventory, Cart& cart, Customer& customer) {
    while (1) {
        UI::displayMenu({
            "---------- CHOOSE YOUR BEST MUSIC ----------",
            "1. See music list",
            "2. Find item",
            "3. Add to cart",
            "4. Purchase",
            "5. Log out"
        });
        int choice = stoi(UI::getInput("Input choice: "));

        switch (choice) {
            case 1: {
                vector<MusicItem> allItems = inventory.getAllItems();
                for (int i = 0; i < allItems.size(); ++i) {
                    allItems[i].displayItems();
                }
                break;
            }
            case 2: {
                string keyword = UI::getInput("Enter keyword: ");
                vector<MusicItem> results = inventory.searchItems(keyword);
                if (results.empty()) {
                    cout << "No items found!\n";
                } else {
                    cout << "Search results: \n";
                    for (int i = 0; i < results.size(); ++i) {
                        results[i].displayItems();
                    }
                }
                break;
            }
            case 3: {
                
                int itemID = stoi(UI::getInput("Enter item ID: "));

                vector<MusicItem> allItems = inventory.getAllItems();

                MusicItem* item = nullptr;
                for (int i = 0; i < allItems.size(); ++i) {
                    if (allItems[i].getID() == itemID) {
                        item = &allItems[i];
                    }
                }
                if (item) {
                    cart.addItems(*item);
                    cout << "Item added to cart!\n";
                } else {
                    cout << "Item is out of stock!\n";
                }

                break;
            }
            case 4: {
                if (cart.getItems().empty()) {
                    cout << "Cart is empty!\n";
                } else {
                    float total = cart.calculateTotal();
                    cout << "Total: $" << total << '\n';

                    string applyDiscount = UI::getInput("Apply discount? yes/no: ");
                    if (applyDiscount == "yes") {
                        string discountType = UI::getInput("Discount type (percentage/fixed): ");
                        float value = stof(UI::getInput("Discount value: "));
                        
                        Discount* discount = DiscountFactory::createDiscount(discountType, value);
                        cart.applyDiscount(discount);
                        
                        total = cart.calculateTotal();
                        
                        cout << "New total: $" << total << '\n';

                    }
                }

                break;
            }
            case 5: {
                return;
            }
            default:
            cout << "Invalid choice. Please try again!\n";
        }
    }
}