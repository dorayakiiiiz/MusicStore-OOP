#include "CustomerController.h"
#include "utils.h"
#include "MusicService.h"
#include "CustomerUI.h"
#include "windows.h"

using std::to_string;

void CustomerController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {
    Cart cart;
    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    while (1) {
        system("cls");

        printMessage("WELCOME CUSTOMER: " + customer->getUsername());
        CustomerUI::displayMenu();
        int choice = stoi(getInput("Input choice: "));

        switch (choice) {
            case 1: {
                system("cls");
                vector<Order> orderHistory;
                for (const auto& order : orders) {
                    if (order.getUsername() == customer->getUsername()) {
                        orderHistory.push_back(order);
                    }
                }

                printHeader("PURCHASE HISTORY");
                CustomerUI::displayPurchasedHistory(orderHistory, customer->getUsername());
                printDashLine();
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                printHeader("MUSIC LIST");
                CustomerUI::displayMusicList(items);
                printDashLine();
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                printHeader("SEARCH ENGINE");

                string keyword = getInput("Enter keyword: ");
                vector<Music> results = MusicService::searchMusicItem(items, keyword);

                if (results.empty()) {
                    printMessage("No results found!");
                } else {
                    printMessage("Search results: ");
                    for (int i = 0; i < results.size(); ++i) {
                        CustomerUI::displayMusicList(results);
                    }
                }
                printDashLine();
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                printHeader("ADD TO CART");

                int itemID = stoi(getInput("Enter item ID: "));
                int quantity = stoi(getInput("Enter quantity: "));

                if (itemID < 1 || itemID > items.size()) {
                    printMessage("Invalid item ID!");
                    break;
                }

                Music item = items[itemID - 1];

                if (quantity <= 0) {
                    printMessage("Invalid quantity!");
                    break;
                }
                if (item.getQuantity() < quantity) {
                    printMessage("Not enough items in stock!");
                    break;
                }
                
                cart.addItems(item, quantity);
                items[itemID - 1].updateQuantity(items[itemID - 1].getQuantity() - quantity);

                printMessage("Added " + to_string(quantity) + " " + item.getName() + " to cart successfully!");

                printHeader("YOUR CURRENT CART");
                cart.displayCart();
                printDashLine();

                system("pause");
                break;
            }
            case 5: {
                system("cls");
                printHeader("REMOVE ITEMS FROM CART");
                if (cart.getItems().empty()) {
                    printMessage("Cart is empty!");
                } else {
                    printMessage("Your current cart: ");
                    cart.displayCart();
                    int itemID = stoi(getInput("Enter item ID to remove: "));
                    if (itemID < 1 || itemID > cart.getItems().size()) {
                        printMessage("Invalid item ID!");
                        break;
                    }

                    // add item quantity back to inventory
                    for (int i = 0; i < items.size(); ++i) {
                        if (items[i] == cart.getItems()[itemID - 1]) {
                            items[i].updateQuantity(items[i].getQuantity() + cart.getItems()[itemID - 1].getQuantity());
                            break;
                        }
                    }
                    
                    cart.removeItem(itemID - 1);
                    printMessage("Removed item successfully!");
                    printHeader("YOUR CURRENT CART");
                    cart.displayCart();
                }
                printDashLine();
                system("pause");

                break;
            }
            case 6: {
                system("cls");
                printHeader("CHECK OUT");
                if (cart.getItems().empty()) {
                    printMessage("Cart is empty! Please add items to cart before checking out.");
                } else {
                    printMessage("Your order details: ");
                    printMessage("Username: " + customer->getUsername());
                    printMessage("Purchased items: ");
                    cart.displayCart();

                    float total = cart.calculateTotal();
                    printMessage("Total: $" + to_string(total));
                    printDashLine();

                    vector<shared_ptr<IDiscount>> validVouchers = DiscountFactory::loadValidDiscounts(vouchers, customer->getUsername());
                    
                    if (!validVouchers.empty()) {
                        printMessage("You have the following vouchers available: ");
                        for (int i = 0; i < validVouchers.size(); ++i) {
                            cout << i + 1 << ". " << validVouchers[i]->toString() << '\n';
                        }
                        string apply = getInput("Do you want to use a voucher? (yes/no): ");
                        if (apply == "yes") {
                            string code = getInput("Enter voucher code: ");
                            shared_ptr<IDiscount> voucher = IDiscount::toDiscount(code);
                            if (DiscountFactory::isValidDiscount(validVouchers, voucher)) {
                                
                                float discount = DiscountFactory::applyDiscount(voucher, total);
                                
                                printMessage("Voucher applied successfully!");
                                printMessage("New total: $" + to_string(discount));
                                total = discount;

                            } else {
                                printMessage("Invalid voucher code!");
                                printMessage("Remaining total: $" + to_string(total));
                            }

                            DiscountFactory::removeDiscount(validVouchers, code);
                        } else {
                            printMessage("No voucher applied.");
                            printMessage("Remaining total: $" + to_string(total));
                        }

                    }

                    map<int, shared_ptr<IDiscount>> discountMap = {
                        {1, make_shared<PercentageDiscount>(customer->getUsername(), 10)},
                        {2, make_shared<FixedDiscount>(customer->getUsername(), 10)}
                    };

                    if (total > 50) {
                        printMessage("Congratulations! As the total is over $50, you will receive a discount voucher for your next purchase");
                        printMessage("What type of discount would you like to apply?");
                        printMessage("1. Percentage discount");
                        printMessage("2. Fixed amount discount");

                        int discountChoice = stoi(getInput("Enter your choice: "));

                        if (discountChoice == 1 || discountChoice == 2) {
                            printMessage("Discount code: " + discountMap[discountChoice]->toString());  
                            vouchers.push_back(discountMap[discountChoice]);
                
                        } else {
                            printMessage("Invalid choice! No discount voucher will be applied.");
                        }
                    }

                    Order order(customer->getUsername(), cart.getItems(), total);
                    orders.push_back(order);
                    cart.clear();

                    printMessage("Order placed successfully! Thank you for your purchase!");
                }
                printDashLine();
                system("pause");
                break;
            }
            case 7: {
                if (cart.getItems().empty()) {
                    printMessage("You have logged out successfully!");
                    currentUser = nullptr;
                    Sleep(1000);
                    return;
                } else {
                    printMessage("You have items in your cart! Please check out before logging out.");
                    Sleep(1000);
                    break;
                }
            }
            default:
                printMessage("Invalid choice! Please try again.");
                Sleep(1000);
        }
    }
}