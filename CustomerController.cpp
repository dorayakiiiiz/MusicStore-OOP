#include "CustomerController.h"
#include "DiscountFactory.h"
#include "User.h"
#include "OrderDAO.h"
#include "VoucherDAO.h"
#include "MusicDAO.h"
#include "utils.h"

#include <sstream>
using std::stringstream, std::string, std::cout, std::endl, std::vector, std::make_shared, std::shared_ptr, std::endl;
using std::cout;
void CustomerController::run(InventoryManager& inventory, Cart& cart, Customer& customer) {
    while (1) {
        displayMenu({
            "---------- CHOOSE YOUR BEST MUSIC ----------\n",
            "1. See your purchased history",
            "2. See music list",
            "3. Find item",
            "4. Add to cart",
            "5. Check out",
            "6. Log out\n",
        });
        int choice = stoi(getInput("Input choice: "));

        switch (choice) {
            case 1: {
                vector<Order> orders;
                OrderDAO::loadOrder(orders);
                bool hasPurchase = false;
                int idx = 1;
                cout << "\n---------- YOUR PURCHASE HISTORY ----------\n";
                for (const auto& order : orders) {
                    if (order.getUsername() == customer.getUsername()) {
                        cout << "Order " << idx++ << ":\n";
                        cout << "Items purchased:\n";
                        for (const auto& item : order.getPurchasedItems()) {
                            hasPurchase = true;
                            cout << " - " << item.getName() << " - Quantity: " << item.getQuantity()
                                 << " - Price per unit: $" << item.getPrice()
                                 << " - Total: $" << item.getPrice() * item.getQuantity() << '\n';
                        }
                        cout << "Order total: $" << order.getTotal() << '\n';
                    }
                }
                if (!hasPurchase) {
                    cout << "\nNo purchase history found!\n";
                } else {
                    cout << "------------------------------------------\n";
                }
                break;
            }
            case 2: {
                vector<Music> allItems = inventory.getAllItems();
                for (int i = 0; i < allItems.size(); ++i) {
                    cout << i + 1 << ". ";
                    allItems[i].displayItems();
                }
                break;
            }
            case 3: {
                string keyword = getInput("Enter keyword: ");
                vector<Music> results = inventory.searchItems(keyword);
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
            case 4: {
                
                int itemID = stoi(getInput("Enter item ID: "));
                int quantity = stoi(getInput("Enter quantity: "));

                vector<Music> allItems = inventory.getAllItems();

                if (itemID < 1 || itemID > allItems.size()) {
                    cout << "\nInvalid item ID!\n";
                    break;
                }

                Music item = allItems[itemID - 1];

                if (quantity <= 0) {
                    cout << "\nInvalid quantity!\n";
                    break;
                }
                if (item.getQuantity() < quantity) {
                    cout << "\nNot enough items in stock!\n";
                    break;
                }
                item.updateQuantity(quantity);
                cart.addItems(item);
                cout << "\nAdded " << quantity << " of " << item.getName() << " to cart.\n";

                cout << "Cart now:\n";
                for (int i = 0; i < cart.getItems().size(); ++i) {
                    cout << i + 1 << ". ";
                    auto item = cart.getItems()[i];
                    item.displayItems();
                }

                break;
            }
            case 5: {
                if (cart.getItems().empty()) {
                    cout << "\nCart is empty!\n";
                } else {
                    vector<Music>& inventoryItems = inventory.getAllItems();
                    
                    // update inventory quantities
                    for (const auto& item : cart.getItems()) {
                        for (auto& inventoryItem : inventoryItems) {
                            if (inventoryItem == item) {
                                inventoryItem.updateQuantity(inventoryItem.getQuantity() - item.getQuantity());
                                break;
                            }
                        }
                    }

                    vector<Music> purchasedHistory;
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
                    
                    string applyDiscount = getInput("\nApply discount? (yes/no): ");
                    if (applyDiscount == "yes") {
                        string code = getInput("Enter code: ");
                        float discount = DiscountFactory::getInstance()->applyDiscount(code, total);
                        if (discount == -1) {
                            cout << "\nInvalid discount code!\n";
                        } else {
                            cout << "\nDiscount applied! New total: $" << discount << '\n';
                            total = discount;
                        }               
                        cout << "\nNew total: $" << total << '\n';
                    }

                    if (total > 50) {
                        cout << "Congratulations! As the total is over $50, you will receive a discount voucher.\n";
                        string receiveVoucher = getInput("Do you want to receive it? (yes/no): ");
                        if (receiveVoucher == "yes") {
                            cout << "What type of discount would you like to apply?\n";
                            cout << "1. Percentage discount\n";
                            cout << "2. Fixed amount discount\n";
                            int discountChoice = stoi(getInput("Enter your choice: "));
                            vector<string> vouchers;
                            VoucherDAO::loadVoucher(vouchers);
                            if (discountChoice == 1) {
                                cout << "You have received a percentage discount voucher!\n";
                                string code = customer.getUsername() + "P" + "10";
                                cout << "Discount code: " << code << '\n';
                                // save the code to the database
                                vouchers.push_back(code);
                                VoucherDAO::saveVoucher(vouchers);
                            } else if (discountChoice == 2) {
                                cout << "You have received a fixed amount discount voucher!\n";
                                string code = customer.getUsername() + "F" + "20";
                                cout << "Discount code: " << code << '\n';
                                // save the code to the database
                                vouchers.push_back(code);
                                VoucherDAO::saveVoucher(vouchers);
                            } else {
                                cout << "Invalid choice!\n";
                            } 
                        } else {
                            cout << "No discount voucher received.\n";
                        }

                    }

                    Order order(customer.getUsername(), purchasedHistory, total);
                    OrderDAO::saveOrder(order);
                    customer.addPurchase(order);
                    cart.clear();

                    MusicDAO::saveItems(inventoryItems);

                    cout << "\nThank you for your purchase!\n";
                    cout << "------------------------------------------\n";

                }
                break;
            }
            case 6: {
                return;
            }
            default:
            cout << "\nInvalid choice. Please try again!\n";
        }
    }
}