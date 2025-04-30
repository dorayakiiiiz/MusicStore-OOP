#include "CustomerController.h"
#include "utils.h"
#include "MusicService.h"

void CustomerController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {
    Cart cart;
    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    while (1) {
        cout << "\n---------- WELCOME CUSTOMER: " << customer->getUsername() << " ----------\n";
        vector<string> options = {
            "---------- MENU ----------\n",
            "1. See your purchased history",
            "2. See music list",
            "3. Find item",
            "4. Add to cart",
            "5. Remove items from cart",
            "6. Check out",
            "7. Log out\n",
        };

        displayMenu(options);
        int choice = stoi(getInput("Input choice: "));

        switch (choice) {
            case 1: {
                vector<Order> orderHistory;
                for (const auto& order : orders) {
                    if (order.getUsername() == customer->getUsername()) {
                        orderHistory.push_back(order);
                    }
                }
                cout << "\n---------- YOUR PURCHASE HISTORY ----------\n";
                if (orderHistory.empty()) {
                    cout << "\nNo purchase history found!\n";
                } else {
                    for (int i = 0; i < orderHistory.size(); ++i) {
                        cout << "Order " << i + 1 << ": \n";
                        vector<Music> items = orderHistory[i].getPurchasedItems();
                        for (const auto& item : items) {
                            cout << " - " << item.getName() << " - Quantity: " << item.getQuantity()
                            << " - Price per unit: $" << item.getPrice()
                            << " - Total: $" << item.getPrice() * item.getQuantity() << '\n';
                        }
                        cout << "Order total: $" << orderHistory[i].getTotal() << '\n';
                        cout << "-----------------------------------------\n";
                    }
                }
                cout << "------------------------------------------\n";
                break;
            }
            case 2: {
                cout << "\n---------- MUSIC LIST ----------\n";
                for (int i = 0; i < items.size(); ++i) {
                    cout << i + 1 << ". ";
                    items[i].displayItems();
                }
                cout << "------------------------------------------\n";
                break;
            }
            case 3: {
                cout << "\n---------- SEARCH ENGINE ----------\n";
                string keyword = getInput("Enter keyword: ");
                vector<Music> results = MusicService::searchMusicItem(items, keyword);
                if (results.empty()) {
                    cout << "\nNo items found!\n";
                } else {
                    cout << "\nSearch results: \n";
                    for (int i = 0; i < results.size(); ++i) {
                        results[i].displayItems();
                    }
                }
                cout << "------------------------------------------\n";
                break;
            }
            case 4: {
                cout << "\n---------- ADD TO CART ----------\n";
                int itemID = stoi(getInput("Enter item ID: "));
                int quantity = stoi(getInput("Enter quantity: "));

                if (itemID < 1 || itemID > items.size()) {
                    cout << "\nInvalid item ID!\n";
                    break;
                }

                Music item = items[itemID - 1];

                if (quantity <= 0) {
                    cout << "\nInvalid quantity!\n";
                    break;
                }
                if (item.getQuantity() < quantity) {
                    cout << "\nNot enough items in stock!\n";
                    break;
                }
                
                cart.addItems(item, quantity);
                items[itemID - 1].updateQuantity(items[itemID - 1].getQuantity() - quantity);

                cout << "\nAdded " << quantity << " of " << item.getName() << " to cart.\n";

                cout << "---------- CURRENT CART ----------\n";
                cart.displayCart();
                cout << "------------------------------------------\n";
                break;
            }
            case 5: {
                cout << "\n---------- YOUR CART ----------\n";
                if (cart.getItems().empty()) {
                    cout << "\nCart is empty!\n";
                } else {
                    cart.displayCart();
                    int itemID = stoi(getInput("Enter item ID to remove: "));
                    if (itemID < 1 || itemID > cart.getItems().size()) {
                        cout << "\nInvalid item ID!\n";
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
                    cout << "\nItem removed from cart.\n";
                    
                }
                break;
            }
            case 6: {
                cout << "\n---------- CHECK OUT ----------\n";
                if (cart.getItems().empty()) {
                    cout << "\nCart is empty!\n";
                } else {

                    cout << "Your order details:\n";
                    cout << "Username: " << customer->getUsername() << '\n';
                    cout << "Items purchased:\n";
                    cart.displayCart();

                    float total = cart.calculateTotal();
                    cout << "Order total: $" << total << '\n';
                    cout << "------------------------------------------\n";

                    vector<shared_ptr<IDiscount>> validVouchers = DiscountFactory::loadValidDiscounts(vouchers, customer->getUsername());
                    
                    if (!validVouchers.empty()) {
                        cout << "You have the following vouchers:\n";
                        for (int i = 0; i < validVouchers.size(); ++i) {
                            cout << i + 1 << ". " << validVouchers[i]->toString() << '\n';
                        }
                        string apply = getInput("Do you want to use a voucher? (yes/no): ");
                        if (apply == "yes") {
                            string code = getInput("Enter voucher code: ");
                            shared_ptr<IDiscount> voucher = IDiscount::toDiscount(code);
                            if (DiscountFactory::isValidDiscount(validVouchers, voucher)) {
                                
                                float discount = DiscountFactory::applyDiscount(voucher, total);
                                
                                cout << "\nVoucher applied! You have received a discount of: $" << total - discount << '\n';
                                cout << "New total: $" << discount << '\n';
                                total = discount;

                            } else {
                                cout << "\nInvalid voucher code!\n";
                                cout << "Remaining total: $" << total << '\n';
                            }

                            DiscountFactory::removeDiscount(validVouchers, code);
                        } else {
                            cout << "\nNo voucher applied.\n";
                            cout << "Remaining total: $" << total << '\n';
                        }

                    }

                    map<int, shared_ptr<IDiscount>> discountMap = {
                        {1, make_shared<PercentageDiscount>(customer->getUsername(), 10)},
                        {2, make_shared<FixedDiscount>(customer->getUsername(), 10)}
                    };

                    if (total > 50) {
                        cout << "Congratulations! As the total is over $50, you will receive a discount voucher for your next purchase.\n";
                        cout << "What type of discount would you like to apply? \n";
                        cout << "1. Percentage discount\n";
                        cout << "2. Fixed amount discount\n";
                        int discountChoice = stoi(getInput("Enter your choice: "));

                        if (discountChoice == 1 || discountChoice == 2) {
                            cout << "Discount code: " << discountMap[discountChoice]->toString() << '\n';
                            vouchers.push_back(discountMap[discountChoice]);
                
                        } else {
                            cout << "Invalid choice. No discount voucher will be applied.\n";
                        }
                    }

                    Order order(customer->getUsername(), cart.getItems(), total);
                    orders.push_back(order);
                    cart.clear();

                    cout << "\nThank you for your purchase!\n";
                    cout << "------------------------------------------\n";

                }
                break;
            }
            case 7: {
                if (cart.getItems().empty()) {
                    cout << "\nYou have logged out successfully!\n";
                    return;
                } else {
                    cout << "\nYou have items in your cart. Please check out before logging out.\n";
                    break;
                }
            }
            default:
            cout << "\nInvalid choice. Please try again!\n";
        }
    }
}