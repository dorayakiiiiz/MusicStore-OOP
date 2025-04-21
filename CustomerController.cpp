#include "CustomerController.h"
#include "DiscountFactory.h"

#include <sstream>
using std::stringstream;

void CustomerController::run(InventoryManager& inventory, Cart& cart, Customer& customer) {
    while (1) {
        UI::displayMenu({
            "---------- CHOOSE YOUR BEST MUSIC ----------\n",
            "1. See music list",
            "2. Find item",
            "3. Add to cart",
            "4. Check out",
            "5. Log out\n",
        });
        int choice = stoi(UI::getInput("Input choice: "));

        switch (choice) {
            case 1: {
                vector<MusicItem> allItems = inventory.getAllItems();
                for (int i = 0; i < allItems.size(); ++i) {
                    cout << i + 1 << ". ";
                    allItems[i].displayItems();
                }
                break;
            }
            case 2: {
                string keyword = UI::getInput("Enter keyword: ");
                vector<MusicItem> results = inventory.searchItems(keyword);
                if (results.empty()) {
                    cout << "\nNo items found!\n";
                } else {
                    cout << "\nSearch results: \n";
                    for (int i = 0; i < results.size(); ++i) {
                        results[i].displayItems();
                    }
                }
                break;
            }
            case 3: {
                
                int itemID = stoi(UI::getInput("Enter item ID: "));
                int quantity = stoi(UI::getInput("Enter quantity: "));

                vector<MusicItem> allItems = inventory.getAllItems();

                if (itemID < 1 || itemID > allItems.size()) {
                    cout << "\nInvalid item ID!\n";
                    break;
                }

                MusicItem item = allItems[itemID - 1];
                if (item.getQuantity() < quantity) {
                    cout << "\nNot enough items in stock!\n";
                    break;
                }
                item.updateQuantity(quantity);
                cart.addItems(item);
                cout << "\nAdded " << quantity << " of " << item.getName() << " to cart.\n";

                break;
            }
            case 4: {
                if (cart.getItems().empty()) {
                    cout << "\nCart is empty!\n";
                } else {
                    vector<MusicItem>& inventoryItems = inventory.getAllItems();
                    
                    // update inventory quantities
                    for (const auto& item : cart.getItems()) {
                        for (auto& inventoryItem : inventoryItems) {
                            if (inventoryItem == item) {
                                inventoryItem.updateQuantity(inventoryItem.getQuantity() - item.getQuantity());
                                break;
                            }
                        }
                    }

                    vector<MusicItem> purchasedHistory;
                    for (const auto& items : cart.getItems()) {
                        purchasedHistory.emplace_back(items);
                    }

                    cout << "Your order details:\n";
                    cout << "Username: " << customer.getUsername() << '\n';
                    cout << "Items purchased:\n";
                    for (const auto& item : cart.getItems()) {
                        cout << " - " << item.getName() << " - Quantity: " << item.getQuantity()
                             << " - Price per unit: $" << item.getPrice()
                             << " - Total: $" << item.getPrice() * item.getQuantity() << '\n';
                    }
                    float total = cart.calculateTotal();
                    cout << "Order total: $" << total << '\n';
                    cout << "------------------------------------------\n";
                    
                    string applyDiscount = UI::getInput("\nApply discount? (yes/no): ");
                    if (applyDiscount == "yes") {
                        string discountType = UI::getInput("Discount type (percentage/fixed): ");
                        float value = stof(UI::getInput("Discount value: "));
                        
                        unique_ptr<Discount> discount = DiscountFactory::createDiscount(discountType, value);
                        cart.applyDiscount(move(discount));
                        
                        total = cart.calculateTotal();
                        
                        cout << "\nNew total: $" << total << '\n';
                    }

                    Order order(customer.getUsername(), purchasedHistory, total);
                    Database::getInstance()->saveOrder(order);
                    customer.addPurchase(order);
                    cart.clear();

                    Database::getInstance()->saveItems(inventoryItems);

                    cout << "\nThank you for your purchase!\n";
                    cout << "------------------------------------------\n";

                }
                break;
            }
            case 5: {
                return;
            }
            default:
            cout << "\nInvalid choice. Please try again!\n";
        }
    }
}