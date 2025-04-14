#include "CustomerController.h"
#include "DiscountFactory.h"


void CustomerController::run(InventoryManager& inventory, Cart& cart, Customer& customer) {
    while (1) {
        UI::displayMenu({
            "---------- CHOOSE YOUR BEST MUSIC ----------",
            "1. See music list",
            "2. Find item",
            "3. Add to cart",
            "4. Check out",
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
                int quantity = stoi(UI::getInput("Enter quantity: "));

                vector<MusicItem> allItems = inventory.getAllItems();

                MusicItem* item = nullptr;
                for (auto& inventoryItem : allItems) {
                    if (inventoryItem.getID() == itemID) {
                        if (inventoryItem.getQuantity() < quantity) {
                            cout << "Not enough stock!\n";
                        }
                        item = &inventoryItem;
                        break;
                    }
                }
                if (item) {
                    cart.addItems(*item, quantity);
                    cout << "Added to cart!\n";
                } else {
                    cout << "Item not found!\n";
                }

                break;
            }
            case 4: {
                if (cart.getItems().empty()) {
                    cout << "Cart is empty!\n";
                } else {
                    float total = cart.calculateTotal();
                    cout << "Total: $" << total << '\n';

                    string applyDiscount = UI::getInput("Apply discount? (yes/no): ");
                    if (applyDiscount == "yes") {
                        string discountType = UI::getInput("Discount type (percentage/fixed): ");
                        float value = stof(UI::getInput("Discount value: "));
                        
                        unique_ptr<Discount> discount = DiscountFactory::createDiscount(discountType, value);
                        cart.applyDiscount(move(discount));
                        
                        total = cart.calculateTotal();
                        
                        cout << "New total: $" << total << '\n';
                    }

                    auto inventoryItems = inventory.getAllItems();
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
                    Order order(customer.getUsername(), purchasedHistory, cart.calculateTotal());
                    Database::getInstance()->saveOrder(order);
                    customer.addPurchase(order);
                    cart.clear();
                    Database::getInstance()->saveItems(inventory.getAllItems());
                    cout << "Purchase completed. Order ID: " << order.getOrderId() << '\n';
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