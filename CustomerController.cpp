

/************************************************************************************
 * @file CustomerController.cpp
 * @brief Implementation of the CustomerController class, which handles customer operations
 *        in a music store application.
 ************************************************************************************/

#include "CustomerController.h"
#include "CustomerUI.h"
#include "DiscountService.h"
#include "MusicService.h"
#include "CartService.h"
#include "OrderService.h"
#include "windows.h"
#include "utils.h"
#include "InputValidator.h"
#include "Registry.h"
#include "IRepository.h"
#include "IMusicRepository.h"
#include "IOrderRepository.h"
#include "IDiscountRepository.h"
#include "IUserRepository.h"

#include <memory>

using std::to_string, std::tie;

// Constructor for CustomerController
CustomerController::CustomerController() {};

// Implements the customer menu interface and all customer operations
void CustomerController::menu(shared_ptr<User>& currentUser) {
    

    // Create a shopping cart for the current session
    Cart cart;
    
    // Cast the User pointer to Customer type for customer-specific operations
    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    
    // Main customer menu loop
    while (true) {
        clearScreen();
        CustomerUI::displayWelcomeMessage(customer->getUsername());
        CustomerUI::displayMenu();
        
        // Get user choice with validation
        int choice;
        bool isValid;
        Error error;    
        do {
            std::tie(isValid, choice, error) = InputValidator::validateInt("Enter your choice: ", 1, 7);
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        switch (choice) {
            case CustomerOption::PURCHASE_HISTORY: { // Purchase History
                handlePurchaseHistory(customer);
                break;
            }
            case CustomerOption::CUSTOMER_MUSIC_LIST: { // Music List
                handleMusicList();
                break;
            }
            case CustomerOption::SEARCH_ENGINE: { // Search Engine
                handleSearch();
                break;
            }
            case CustomerOption::ADD_TO_CART: { // Add to Cart
                handleAddToCart(cart);
                break;
            }
            case CustomerOption::REMOVE_FROM_CART: { // Remove from Cart
                handleRemoveFromCart(cart);
                break;
            }
            case CustomerOption::CHECKOUT: { // Checkout
                handleCheckout(cart, customer);
                break;
            }
            case CustomerOption::CUSTOMER_LOGOUT: { // Logout
                if (handleLogout(cart, currentUser)) {
                    return; // Exit the menu loop if logout is successful
                } else {
                    continue; // Stay in the menu if logout is not allowed
                }
            }
            default:
                sleepScreen();
        }
    }
}

// handle the first case of the menu: display purchase history
void CustomerController::handlePurchaseHistory(Customer*& customer) {
    clearScreen();

    auto orderService = Registry::getSingleton<OrderService>();

    vector<Order> orders = Registry::getSingleton<IOrderRepository>()->getAll();

    // Get order history for the current customer
    vector<Order> orderHistory = orderService->getUserOrders(orders, customer->getUsername());

    printHeader("PURCHASE HISTORY");
    CustomerUI::displayPurchasedHistory(orderHistory, customer->getUsername());
    printDashLine();
    pauseScreen();
}

// handle the second case of the menu: display music list
void CustomerController::handleMusicList() {
    clearScreen();
    printHeader("MUSIC LIST");

    vector<Music> items = Registry::getSingleton<IMusicRepository>()->getAll();
    CustomerUI::displayMusicList(items);

    printDashLine();
    pauseScreen();
}

// handle the third case of the menu: search engine
void CustomerController::handleSearch() {

    // get the music service instance
    auto musicService = Registry::getSingleton<MusicService>();
    // get all music items from the repository
    vector<Music> items = Registry::getSingleton<IMusicRepository>()->getAll();
    while (1) {
        clearScreen();
        printHeader("SEARCH ENGINE");

        int criteria;
        string keyword;
        
        // Get search criteria with validation
        bool isValid;
        Error error;
        do {
            tie(isValid, criteria, error) = InputValidator::validateInt("Enter search criteria (1 for name, 2 for artist, 3 for genre): ", 1, 3);
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        // Get search keyword with validation
        do {
            tie(isValid, keyword, error) = InputValidator::validateString("Enter keyword: ");
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        // Perform search and display results
        vector<Music> results = musicService->searchMusic(items, static_cast<SearchType>(criteria), keyword);

        if (results.empty()) {
            CustomerUI::displayNoResultsMessage();
        } else {
            CustomerUI::displaySearchResults(results);
        }

        printDashLine();
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }
}

// handle the fourth case of the menu: add to cart
void CustomerController::handleAddToCart(Cart& cart) {
    clearScreen();
    printHeader("ADD TO CART");

    // Get all music items from the repository
    vector<Music> items = Registry::getSingleton<IMusicRepository>()->getAll();

    // Display current music list
    CustomerUI::displayMusicList(items);
    printDashLine();

    auto cartService = Registry::getSingleton<CartService>();
    while (1) {
        
        // Get item ID and quantity from user
        int itemID, quantity;
        bool isValid;
        Error error;

        // Get item ID with validation
        do {
            tie(isValid, itemID, error) = InputValidator::validateInt("Enter item ID: ", 1, items.size());
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        // Get quantity with validation
        do {
            tie(isValid, quantity, error) = InputValidator::validateInt("Enter quantity: ", 1, INT_MAX);
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        // Add item to cart
        if (cartService->addItemToCart(cart, itemID - 1, quantity)) {
            printMessage("Added " + to_string(quantity) + " " + items[itemID - 1].getName() + " to cart successfully!");
        } else {
            printMessage("Failed to add item. Insufficient stock!");
        }

        printHeader("YOUR CURRENT CART");
        CustomerUI::displayCart(cart.getItems());

        printDashLine();
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }
}

// handle the fifth case of the menu: remove from cart
void CustomerController::handleRemoveFromCart(Cart& cart) {
    clearScreen();
    printHeader("REMOVE ITEMS FROM CART");

    auto cartService = Registry::getSingleton<CartService>();

    // Get all music items from the repository
    vector<Music> items = Registry::getSingleton<IMusicRepository>()->getAll();

    if (cart.getItems().empty()) {
        printMessage("Cart is empty!");
    } else {
        printMessage("Your current cart: ");
        CustomerUI::displayCart(cart.getItems());

        while (1) {
            // Get item ID to remove with validation
            int itemID;
            bool isValid;
            Error error;
            do {
                tie(isValid, itemID, error) = InputValidator::validateInt("Enter item ID to remove: ", 1, cart.getItems().size());
                if (!isValid) {
                    printMessage(error.message);
                    sleepScreen();
                    continue;
                }
            } while (!isValid);

            // Remove item from cart
            if (cartService->removeItemFromCart(cart, items, itemID - 1)) {
                printMessage("Removed item successfully!");
                if (cart.getItems().empty()) {
                    printMessage("Cart is empty!");
                } else {
                    printMessage("YOUR CURRENT CART: ");
                    CustomerUI::displayCart(cart.getItems());
                }
            } else {
                printMessage("Invalid item ID!");
            }
            printDashLine();
            if (cart.getItems().empty()) {
                pauseScreen();
                break;
            }
            printRepeatMessage();

            char repeat = _getch();
            if (repeat == ' ') {
                break;
            }
        }
    }
    pauseScreen();
}

// handle the sixth case of the menu: checkout
void CustomerController::handleCheckout(Cart& cart, Customer*& customer) {
    clearScreen();
    printHeader("CHECK OUT");

    bool isValid;
    Error error;

    auto orderService = Registry::getSingleton<OrderService>();
    auto musicService = Registry::getSingleton<MusicService>();
    auto discountService = Registry::getSingleton<DiscountService>();

    // Get all orders and vouchers from the repository
    vector<Order> orders = Registry::getSingleton<IOrderRepository>()->getAll();
    vector<shared_ptr<Discount>> vouchers = Registry::getSingleton<IDiscountRepository>()->getAll();

    if (cart.getItems().empty()) {
        CustomerUI::displayEmptyCartMessage();
    } else {
        // Calculate initial total
        float total = cart.calculateTotal();
        CustomerUI::displayOrderDetails(customer->getUsername(), cart.getItems(), total);
        
        // Handle discount vouchers if available
        vector<shared_ptr<Discount>> validVouchers = 
            discountService->loadValidDiscounts(vouchers, customer->getUsername());
        
        shared_ptr<Discount> selectedVoucher = nullptr;

        if (!validVouchers.empty()) {
            // Display available vouchers
            CustomerUI::displayVoucherList(validVouchers);
            int useVoucher;

            // Ask if user wants to apply a voucher
            do {
                tie(isValid, useVoucher, error) = InputValidator::validateInt("Do you want to use a voucher? (1 for yes, 2 for no): ", 1, 2);
                if (!isValid) {
                    printMessage(error.message);
                    sleepScreen();
                    continue;
                }
            } while (!isValid);

            if (Agreement::YES == useVoucher) {
                // Get voucher code
                string voucherCode;
                do {
                    tie(isValid, voucherCode, error) = InputValidator::validateString("Enter voucher code: ");
                    if (!isValid) {
                        printMessage(error.message);
                        sleepScreen();
                        continue;
                    }
                } while (!isValid);
                
                // Find and apply the selected voucher
                for (const auto& voucher : validVouchers) {
                    if (voucher->toString() == voucherCode) {
                        selectedVoucher = voucher;
                        
                        // Apply the discount to the total
                        total = discountService->applyDiscount(selectedVoucher, total);
                        printMessage("Voucher applied! New total: $" + 
                                                           to_string(total));
                        
                        // Remove the used voucher
                        discountService->removeDiscount(voucherCode);
                        break;
                    } 
                }
                
                if (!selectedVoucher) {
                    printMessage("Invalid voucher code!");
                }
            }
        }
        
        // Create the order with final total
        orderService->checkout(customer->getUsername(), cart, total);

        // Give a new voucher if total is over $50
        if (total > 50) {
            CustomerUI::displayDiscountOptions();

            // Get discount type choice
            int discountChoice;
            do {
                tie(isValid, discountChoice, error) = InputValidator::validateInt("Choose a discount option (1 or 2): ", 1, 2);
                if (!isValid) {
                    printMessage(error.message);
                    sleepScreen();
                    continue;
                }
            } while (!isValid);
            
            // Set discount value based on choice (10% for percentage, $5 for fixed amount)
            int discountValue = (DiscountType::PERCENTAGE == discountChoice) ? 10 : 5;

            // Create and add the new voucher
            discountService->createDiscount(customer->getUsername(),
                                         static_cast<DiscountType>(discountChoice), discountValue);
            // Notify the user about the new voucher
            string notify = (static_cast<DiscountType>(discountChoice) == DiscountType::PERCENTAGE) ? "10% off" : "$5 off";
            printMessage("New voucher created! " + notify + " on your next purchase.");
        }

        CustomerUI::displayOrderSuccessMessage();
        // delete the item that was sold out from the inventory
        musicService->removeSoldOutItems();

    }
    printDashLine();
    pauseScreen();
}

// handle the seventh case of the menu: logout
bool CustomerController::handleLogout(Cart& cart, shared_ptr<User>& currentUser) {
    // Check if cart is empty before allowing logout
    if (cart.getItems().empty()) {
        CustomerUI::displayLogoutMessage();
        currentUser = nullptr;
        sleepScreen();
        return true;
    } else {
        CustomerUI::displayCartWarningMessage();
        sleepScreen();
        return false;
    }
}

