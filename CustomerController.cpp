#include "CustomerController.h"
#include "CustomerUI.h"
#include "CustomerService.h"
#include "windows.h"
#include "utils.h"

using std::to_string;

// Implements the customer menu interface and all customer operations
void CustomerController::menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, 
                            vector<shared_ptr<IDiscount>>& vouchers, shared_ptr<IUser>& currentUser) {
    bool isValid;
    Error error;

    // Create a shopping cart for the current session
    Cart cart;
    
    // Cast the IUser pointer to Customer type for customer-specific operations
    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    
    // Main customer menu loop
    while (1) {
        clearScreen();
        CustomerUI::displayWelcomeMessage(customer->getUsername());
        CustomerUI::displayMenu();
        
        // Get user choice with validation
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
                // Get order history for the current customer
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

                // Get search criteria with validation
                vector<string> options = {"name", "artist", "genre"};
                do {
                    std::tie(isValid, criteria, error) = getStringInput("Enter search criteria (name/artist/genre): ", options);
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                // Get search keyword
                do {
                    std::tie(isValid, keyword, error) = getStringInput("Enter keyword: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                // Perform search and display results
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

                // Get item ID with validation
                do {
                    std::tie(isValid, itemID, error) = getIntInput("Enter item ID: ", 1, items.size());
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                // Get quantity with validation
                do {
                    std::tie(isValid, quantity, error) = getIntInput("Enter quantity: ", 1, INT_MAX);
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                // Add item to cart
                if (CustomerService::addItemToCart(cart, items, itemID - 1, quantity)) {
                    printMessage("Added " + std::to_string(quantity) + " " + 
                                               items[itemID - 1].getName() + " to cart successfully!");
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

                    // Get item ID to remove with validation
                    int itemID;
                    do {
                        std::tie(isValid, itemID, error) = getIntInput("Enter item ID to remove: ", 1, cart.getItems().size());
                        if (!isValid) {
                            printMessage(error.message);
                            Sleep(1000);
                            continue;
                        }
                    } while (!isValid);
                    
                    // Remove item from cart
                    if (CustomerService::removeItemFromCart(cart, items, itemID - 1)) {
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
                    // Calculate initial total
                    float total = cart.calculateTotal();
                    CustomerUI::displayOrderDetails(customer->getUsername(), cart.getItems(), total);
                    
                    // Handle discount vouchers if available
                    vector<shared_ptr<IDiscount>> validVouchers = 
                        DiscountFactory::loadValidDiscounts(vouchers, customer->getUsername());
                    
                    shared_ptr<IDiscount> selectedVoucher = nullptr;
                    if (!validVouchers.empty()) {
                        // Display available vouchers
                        CustomerUI::displayVoucherList(validVouchers);
                        string useVoucher;

                        // Ask if user wants to apply a voucher
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
                            // Get voucher code
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
                            
                            // Find and apply the selected voucher
                            for (const auto& voucher : validVouchers) {
                                if (voucher->toString() == voucherCode) {
                                    selectedVoucher = voucher;
                                    
                                    // Apply the discount to the total
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
                    
                    // Create the order with final total
                    CustomerService::checkout(orders, customer->getUsername(), cart, total);

                    // Give a new voucher if total is over $50
                    if (total > 50) {
                        CustomerUI::displayDiscountOptions();

                        // Get discount type choice
                        int discountChoice;
                        do {
                            std::tie(isValid, discountChoice, error) = getIntInput("Choose a discount option (1 or 2): ", 1, 2);
                            if (!isValid) {
                                printMessage(error.message);
                                Sleep(1000);
                                continue;
                            }
                        } while (!isValid);
                        
                        // Set discount value based on choice (10% for percentage, $5 for fixed amount)
                        int discountValue = (discountChoice == 1) ? 10 : 5;
                        
                        // Create and add the new voucher
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
                // Check if cart is empty before allowing logout
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
                // Invalid choice handling (cannot reach here due to input validation, will remove later)
                CustomerUI::displayInvalidChoiceMessage();
                Sleep(1000);
        }
    }
}