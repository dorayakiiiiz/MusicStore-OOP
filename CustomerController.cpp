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

                MusicItem* item = nullptr;
                for (auto& inventoryItem : allItems) {
                    if (inventoryItem.getID() == itemID) {
                        if (inventoryItem.getQuantity() < quantity) {
                            cout << "\nNot enough stock!\n";
                        }
                        item = &inventoryItem;
                        break;
                    }
                }
                if (item) {
                    cart.addItems(*item, quantity);
                    cout << "\nAdded to cart!\n";
                } else {
                    cout << "\nItem not found!\n";
                }

                break;
            }
            case 4: {
                if (cart.getItems().empty()) {
                    cout << "\nCart is empty!\n";
                } else {
                    float total = cart.calculateTotal();
                    cout << "\nTotal: $" << total << '\n';

                    string applyDiscount = UI::getInput("\nApply discount? (yes/no): ");
                    if (applyDiscount == "yes") {
                        string discountType = UI::getInput("Discount type (percentage/fixed): ");
                        float value = stof(UI::getInput("Discount value: "));
                        
                        unique_ptr<Discount> discount = DiscountFactory::createDiscount(discountType, value);
                        cart.applyDiscount(move(discount));
                        
                        total = cart.calculateTotal();
                        
                        cout << "\nNew total: $" << total << '\n';
                    }

                    vector<MusicItem>& inventoryItems = inventory.getAllItems();
                    for (const auto& [cartItem, quantity] : cart.getItems()) {
                        for (auto& inventoryItem : inventoryItems) {
                            if (inventoryItem.getID() == cartItem.getID()) {
                                inventoryItem.updateQuantity(inventoryItem.getQuantity() - quantity);
                                break;
                            }
                        }
                    }
                    vector<pair<int, int>> purchasedHistory;
                    for (const auto& [items, total] : cart.getItems()) {
                        purchasedHistory.emplace_back(items.getID(), total);
                    }
                    time_t now = time(nullptr);
                    stringstream ss;
                    ss << "ORD-" << now;
                    string orderId = ss.str();
                    Order order(orderId, customer.getUsername(), purchasedHistory, cart.calculateTotal());
                    Database::getInstance()->saveOrder(order);
                    customer.addPurchase(order);
                    cart.clear();

                    Database::getInstance()->saveItems(inventoryItems);
                    cout << "\nPurchase completed. Order ID: " << order.getOrderId() << '\n';
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