#include "CustomerController.h"
#include "CustomerUI.h"
#include "CustomerService.h"
#include "windows.h"
#include "utils.h"

using std::to_string;

void CustomerController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, 
                            vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {
    bool isValid;
    Error error;


    Cart cart;
    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    
    while (1) {
        clearScreen();
        CustomerUI::displayWelcomeMessage(customer->getUsername());
        CustomerUI::displayMenu();
        
        int choice;
        do {
            std::tie(isValid, choice, error) = getIntInput("Enter your choice: ", 1, 7);
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);

        switch (choice) {
            case 1: { // Purchase History
                clearScreen();
                vector<Order> orderHistory = CustomerService::getUserOrders(orders, customer->getUsername());
                
                printHeader("PURCHASE HISTORY");
                CustomerUI::displayPurchasedHistory(orderHistory, customer->getUsername());
                printDashLine();
                pauseScreen();
                break;
            }
            case 2: { // Music List
                clearScreen();
                printHeader("MUSIC LIST");
                CustomerUI::displayMusicList(items);
                printDashLine();
                pauseScreen();
                break;
            }
            case 3: { // Search Engine
                string criteria, keyword;
                clearScreen();
                printHeader("SEARCH ENGINE");

                vector<string> options = {"name", "artist", "genre"};
                do {
                    std::tie(isValid, criteria, error) = getStringInput("Enter search criteria (name/artist/genre): ", options);
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                do {
                    std::tie(isValid, keyword, error) = getStringInput("Enter keyword: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                vector<Music> results = CustomerService::searchMusic(items, criteria, keyword);

                if (results.empty()) {
                    CustomerUI::displayNoResultsMessage();
                } else {
                    CustomerUI::displaySearchResults(results);
                }
                printDashLine();
                pauseScreen();
                break;
            }
            case 4: { // Add to Cart

                int itemID, quantity;
                clearScreen();
                printHeader("ADD TO CART");

                do {
                    std::tie(isValid, itemID, error) = getIntInput("Enter item ID: ", 1, items.size());
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                do {
                    std::tie(isValid, quantity, error) = getIntInput("Enter quantity: ", 1, INT_MAX);
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                itemID -= 1; 

                if (CustomerService::addItemToCart(cart, items, itemID, quantity)) {
                    printMessage("Added " + std::to_string(quantity) + " " + 
                                               items[itemID].getName() + " to cart successfully!");
                } else {
                    printMessage("Failed to add item! Invalid ID or insufficient stock.");
                }
                
                printHeader("YOUR CURRENT CART");
                CustomerUI::displayCart(cart.getItems());
                printDashLine();
                pauseScreen();
                break;
            }
            case 5: { // Remove from Cart
                clearScreen();
                printHeader("REMOVE ITEMS FROM CART");
                
                if (cart.getItems().empty()) {
                    printMessage("Cart is empty!");
                } else {
                    printMessage("Your current cart: ");
                    CustomerUI::displayCart(cart.getItems());

                    int itemID;
                    do {
                        std::tie(isValid, itemID, error) = getIntInput("Enter item ID to remove: ", 1, cart.getItems().size());
                        if (!isValid) {
                            printMessage(error.message);
                            Sleep(1000);
                            continue;
                        }
                    } while (!isValid);
                    
                    if (CustomerService::removeItemFromCart(cart, items, itemID)) {
                        printMessage("Removed item successfully!");
                        printHeader("YOUR CURRENT CART");
                        CustomerUI::displayCart(cart.getItems());
                    } else {
                        printMessage("Invalid item ID!");
                    }
                }
                printDashLine();
                pauseScreen();
                break;
            }
            case 6: { // Checkout
                clearScreen();
                printHeader("CHECK OUT");
                
                if (cart.getItems().empty()) {
                    CustomerUI::displayEmptyCartMessage();
                } else {
                    float total = cart.calculateTotal();
                    CustomerUI::displayOrderDetails(customer->getUsername(), cart.getItems(), total);
                    
                    // Handle vouchers
                    vector<shared_ptr<IDiscount>> validVouchers = 
                        DiscountFactory::loadValidDiscounts(vouchers, customer->getUsername());
                    
                    shared_ptr<IDiscount> selectedVoucher = nullptr;
                    if (!validVouchers.empty()) {
                        CustomerUI::displayVoucherList(validVouchers);
                        string useVoucher;

                        vector<string> options = {"yes", "no"};
                        do {
                            std::tie(isValid, useVoucher, error) = getStringInput("Do you want to use a voucher? (yes/no): ", options);
                            if (!isValid) {
                                printMessage(error.message);
                                Sleep(1000);
                                continue;
                            }
                        } while (!isValid);

                        if (useVoucher == "yes") {
                            bool isValid = true;
                            string voucherCode;
                            do {
                                std::tie(isValid, voucherCode, error) = getStringInput("Enter voucher code: ");
                                if (!isValid) {
                                    printMessage(error.message);
                                    Sleep(1000);
                                    continue;
                                }
                            } while (!isValid);
                            
                            // Find the selected voucher
                            for (const auto& voucher : validVouchers) {
                                if (voucher->toString() == voucherCode) {
                                    selectedVoucher = voucher;
                                    
                                    // Apply the voucher
                                    total = DiscountFactory::applyDiscount(voucher, total);
                                    printMessage("Voucher applied! New total: $" + 
                                                               std::to_string(total));
                                    
                                    // Remove the used voucher
                                    DiscountFactory::removeDiscount(vouchers, voucherCode);
                                    break;
                                }
                            }
                            
                            if (!selectedVoucher) {
                                printMessage("Invalid voucher code!");
                            }
                        }
                    }
                    
                    // Create the order
                    CustomerService::checkout(orders, customer->getUsername(), cart, total);

                    if (total > 50) {
                        CustomerUI::displayDiscountOptions();

                        int discountChoice;
                        do {
                            std::tie(isValid, discountChoice, error) = getIntInput("Choose a discount option (1 or 2): ", 1, 2);
                            if (!isValid) {
                                printMessage(error.message);
                                Sleep(1000);
                                continue;
                            }
                        } while (!isValid);
                        int discountValue = (discountChoice == 1) ? 10 : 5;
                        
                        CustomerService::createNewVoucher(vouchers, customer->getUsername(), 
                                                     discountChoice, discountValue);
                        
                        printMessage("A new voucher has been added to your account!");
                    }
                    CustomerUI::displayOrderSuccessMessage();
                }
                printDashLine();
                pauseScreen();
                break;
            }
            case 7: { // Logout
                if (cart.getItems().empty()) {
                    CustomerUI::displayLogoutMessage();
                    currentUser = nullptr;
                    Sleep(1000);
                    return;
                } else {
                    CustomerUI::displayCartWarningMessage();
                    Sleep(1000);
                    break;
                }
            }
            default:
                CustomerUI::displayInvalidChoiceMessage();
                Sleep(1000);
        }
    }
}