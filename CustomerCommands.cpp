#include "CustomerCommands.h"
#include "CustomerUI.h"
#include "Music.h"
#include "Order.h"
#include "DiscountService.h"
#include "MusicService.h"
#include "CartService.h"
#include "SalesRecordService.h"
#include "OrderService.h"
#include "utils.h"
#include "InputValidator.h"
#include <memory>
#include <conio.h>

enum Agreement {
    YES = 1,
    NO = 0
};

using std::vector, std::string, std::shared_ptr, std::make_shared, std::pair, std::tie, std::to_string;

// ViewPurchaseHistoryCommand implementation
ViewPurchaseHistoryCommand::ViewPurchaseHistoryCommand(shared_ptr<User>& user) : currentUser(user) {}

string ViewPurchaseHistoryCommand::getName() const {
    return "SEE PURCHASE HISTORY";
}

bool ViewPurchaseHistoryCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);

    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    vector<Order> orders = OrderService::getInstance()->getAllOrders();

    // Get order history for the current customer
    vector<Order> orderHistory = OrderService::getInstance()->getUserOrders(customer->getUsername());
    
    string header = "PURCHASE HISTORY";
    printHeader(header, (120 - header.length()*2) / 2 - 40, 2);
    CustomerUI::displayPurchasedHistory(orderHistory, customer->getUsername());

    printDashLine();
    pauseScreen();
    return true;
}

// ViewMusicCommand implementation
std::string ViewMusicCommand::getName() const {
    return "SEE MUSIC LIST";
}

bool ViewMusicCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);

    string header = "MUSIC LIST";
    printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

    vector<Music> items = MusicService::getInstance()->getAllMusic();
    CustomerUI::displayMusicList(items);

    printDashLine();
    pauseScreen();
    return true;
}

// SearchMusicCommand implementation
string SearchMusicCommand::getName() const {
    return "FIND ITEM";
}

bool SearchMusicCommand::execute() {
    // get all music items from the repository
    vector<Music> items = MusicService::getInstance()->getAllMusic();

    clearScreen();
    printFrame(0, 0, 120, 30);
    while (true) {
        string header = "SEARCH MUSIC";
        printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

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
        vector<Music> results = MusicService::getInstance()->searchMusic(items, static_cast<SearchType>(criteria), keyword);

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
    return true;
}

// AddToCartCommand implementation
AddToCartCommand::AddToCartCommand(Cart& c) : cart(c) {}

string AddToCartCommand::getName() const {
    return "ADD TO CART";
}

bool AddToCartCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);
    string header = "ADD TO CART";
    printHeader(header, (120 - header.length()*2) / 2 - 30, 1);

    // Get all music items from the repository
    vector<Music> items = MusicService::getInstance()->getAllMusic();

    // Display current music list
    CustomerUI::displayMusicList(items);
    printDashLine();

    while (true) {
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
        if (CartService::getInstance()->addItemToCart(cart, itemID, quantity)) {
            printMessage("Added " + to_string(quantity) + " " + items[itemID - 1].getName() + " to cart successfully!");
        } else {
            printMessage("Failed to add item. Not enough stock!");
        }

        //printHeader("YOUR CURRENT CART");
        CustomerUI::displayCart(cart.getItems());

        printDashLine();
        printRepeatMessage();

        char repeat = _getch();
        if (repeat == ' ') {
            break;
        }
        printDashLine();
    }
    return true;
}

// RemoveFromCartCommand implementation
RemoveFromCartCommand::RemoveFromCartCommand(Cart& c) : cart(c) {}

std::string RemoveFromCartCommand::getName() const {
    return "REMOVE ITEMS FROM CART";
}

bool RemoveFromCartCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);
    string header = "REMOVE ITEMS FROM CART";
    printHeader(header, (120 - header.length()*2) / 2 - 30, 1);

    // Get all music items from the repository
    vector<Music> items = MusicService::getInstance()->getAllMusic();

    if (cart.getItems().empty()) {
        printMessage("Cart is empty!");
    } else {
        printMessage("Your current cart: ");
        CustomerUI::displayCart(cart.getItems());

        while (true) {
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
            if (CartService::getInstance()->removeItemFromCart(cart, itemID - 1)) {
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
    return true;
}

// CheckoutCommand implementation
CheckoutCommand::CheckoutCommand(Cart& c, shared_ptr<User>& user) : cart(c), currentUser(user) {}

std::string CheckoutCommand::getName() const {
    return "CHECK OUT";
}

bool CheckoutCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);
    string header = "CHECK OUT";
    printHeader(header, (120 - header.length()*2) / 2 - 20, 1);

    bool isValid;
    Error error;
    Customer* customer = dynamic_cast<Customer*>(currentUser.get());

    // Get all orders and vouchers from the repository
    vector<Order> orders = OrderService::getInstance()->getAllOrders();
    vector<shared_ptr<Discount>> vouchers = DiscountService::getInstance()->getAllDiscounts();

    if (cart.getItems().empty()) {
        CustomerUI::displayEmptyCartMessage();
    } else {
        // Calculate initial total
        float total = cart.calculateTotal();
        CustomerUI::displayOrderDetails(customer->getUsername(), cart.getItems(), total);
        
        // Handle discount vouchers if available
        vector<shared_ptr<Discount>> validVouchers = 
            DiscountService::getInstance()->loadValidDiscounts(vouchers, customer->getUsername());

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
                        total = DiscountService::getInstance()->applyDiscount(selectedVoucher, total);
                        printMessage("Voucher applied! New total: $" + to_string(total));
                        
                        // Remove the used voucher
                        DiscountService::getInstance()->removeDiscount(voucherCode);
                        break;
                    } 
                }
                
                if (!selectedVoucher) {
                    printMessage("Invalid voucher code!");
                }
            }
        }

        // add the items purchased to the sales record
        SalesRecordService::getInstance()->addToRecord(cart);
        
        // Create the order with final total
        OrderService::getInstance()->checkout(customer->getUsername(), cart, total);

        // delete the item that was sold out from the inventory
        MusicService::getInstance()->removeSoldOutItems();

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
            DiscountService::getInstance()->createDiscount(customer->getUsername(),
                                         static_cast<DiscountType>(discountChoice), discountValue);
            // Notify the user about the new voucher
            string notify = (static_cast<DiscountType>(discountChoice) == DiscountType::PERCENTAGE) ? "10% off" : "$5 off";
            printMessage("New voucher created! " + notify + " on your next purchase.");
        }

        CustomerUI::displayOrderSuccessMessage();

    }
    
    printDashLine();
    pauseScreen();
    return true;
}

// CustomerLogoutCommand implementation
CustomerLogoutCommand::CustomerLogoutCommand(Cart& c, shared_ptr<User>& user) : cart(c), currentUser(user) {}

std::string CustomerLogoutCommand::getName() const {
    return "LOG OUT";
}

bool CustomerLogoutCommand::execute() {
    // Check if cart is empty before allowing logout
    if (cart.getItems().empty()) {
        CustomerUI::displayLogoutMessage();
        currentUser = nullptr;
        sleepScreen();
        return false; // Exit menu loop
    } else {
        CustomerUI::displayCartWarningMessage();
        sleepScreen();
        return true; // Stay in menu loop
    }
}
