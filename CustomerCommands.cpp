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
#include "InputChecker.h"
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
    
    string header = "purchaseHistory";
    printHeader(header, (120 - header.length()*2) / 2 - 31, 2);
    CustomerUI::displayPurchasedHistory(orderHistory, customer->getUsername());

    //pauseScreen();
    return true;
}

// ViewMusicCommand implementation
std::string ViewMusicCommand::getName() const {
    return "SEE MUSIC LIST";
}

bool ViewMusicCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);

    string header = "musicList";
    printHeader(header, (120 - header.length()*2) / 2 - 19, 1);

    vector<Music> items = MusicService::getInstance()->getAllMusic();
    CustomerUI::displayMusicList(items);

    //pauseScreen();
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
        string header = "searchMusic";
        printHeader(header, (120 - header.length()*2) / 2 - 23, 1);
        
        // Get search criteria with validation
        int criteria = getValidatedInput<int>(
            "Enter search criteria (1 for name, 2 for artist, 3 for genre): ",
            [](const string& prompt) {
                return InputChecker::checkInt(prompt, 10, 10, 1, 3);
            },
            10, 10
        );

        // Get search keyword with validation
        string keyword = getValidatedInput<string>(
            "Enter keyword: ",
            [](const string& prompt) {
                return InputChecker::checkString(prompt, 10, 11);
            },
            10, 11
        );


        // Perform search and display results
        vector<Music> results = MusicService::getInstance()->searchMusic(items, static_cast<SearchType>(criteria), keyword);

        if (results.empty()) {
            CustomerUI::displayNoResultsMessage();
        } else {
            CustomerUI::displaySearchResults(results);
        }

        //printRepeatMessage();

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
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
    string header = "addToCart";
    printHeader(header, (120 - header.length()*2) / 2 - 24, 1);

    // Get all music items from the repository
    vector<Music> items = MusicService::getInstance()->getAllMusic();

    // Display current music list
    CustomerUI::displayMusicList(items);

    while (true) {
        // Get item ID and quantity from user

        // Get item ID with validation
        int itemID = getValidatedInput<int>(
            "Enter item ID: ",
            [&items](const string& prompt) {
                return InputChecker::checkInt(prompt, 10, 25, 1, items.size());
            },
            10, 25
        );

        // Get quantity with validation
        int quantity = getValidatedInput<int>(
            "Enter quantity: ",
            [](const string& prompt) {
                return InputChecker::checkInt(prompt, 10, 26, 1, INT_MAX);
            },
            10, 26
        );

        // Add item to cart
        if (CartService::getInstance()->addItemToCart(cart, itemID, quantity)) {
            printMessage("Added " + to_string(quantity) + " " + items[itemID - 1].getName() + " to cart successfully!", 10, 20);
        } else {
            printMessage("Failed to add item. Not enough stock!", 10, 21);
        }

        //printHeader("YOUR CURRENT CART");
        CustomerUI::displayCart(cart.getItems());

        //printRepeatMessage();

        char repeat = _getch();
        if (27 == repeat) {
            break;
        }
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
    string header = "removeItems";
    printHeader(header, (120 - header.length()*2) / 2 - 24, 1);

    // Get all music items from the repository
    vector<Music> items = MusicService::getInstance()->getAllMusic();

    if (cart.getItems().empty()) {
        printMessage("Cart is empty!", 10, 15);
    } else {
        printMessage("Your current cart: ", 10, 15);
        CustomerUI::displayCart(cart.getItems());

        while (true) {
            // Get item ID to remove with validation
            int itemID = getValidatedInput<int>(
                "Enter item ID to remove: ",
                [this](const string& prompt) {
                    return InputChecker::checkInt(prompt, 10, 20, 1, cart.getItems().size());
                },
                10, 20
            );

            // Remove item from cart
            if (CartService::getInstance()->removeItemFromCart(cart, itemID - 1)) {
                printMessage("Removed item successfully!", 10, 21);
                if (cart.getItems().empty()) {
                    printMessage("Cart is empty!", 10, 22);
                } else {
                    printMessage("YOUR CURRENT CART: ", 10, 23);
                    CustomerUI::displayCart(cart.getItems());
                }
            } else {
                printMessage("Invalid item ID!", 10, 21);
            }
            if (cart.getItems().empty()) {
                //pauseScreen();
                break;
            }
            //printRepeatMessage();

            char repeat = _getch();
            if (27 == repeat) {
                break;
            }
        }
    }
   // pauseScreen();
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
    string header = "checkOut";
    printHeader(header, (120 - header.length()*2) / 2 - 19, 1);

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
            int useVoucher = getValidatedInput<int>(
                "Do you want to use a voucher? (1 for yes, 2 for no): ",
                [](const string& prompt) {
                    return InputChecker::checkInt(prompt, 10, 24, 1, 2);
                },
                10, 24
            );

            if (Agreement::YES == useVoucher) {
                // Get voucher code
                string voucherCode = getValidatedInput<string>(
                    "Enter voucher code: ",
                    [](const string& prompt) {
                        return InputChecker::checkString(prompt, 10, 25);
                    },
                    10, 25
                );
                
                // Find and apply the selected voucher
                for (const auto& voucher : validVouchers) {
                    if (voucher->getCode() == voucherCode) {
                        selectedVoucher = voucher;
                        
                        // Apply the discount to the total
                        total = DiscountService::getInstance()->applyDiscount(selectedVoucher, total);
                        printMessage("Voucher applied! New total: $" + to_string(total), 10, 26);
                        
                        // Remove the used voucher
                        DiscountService::getInstance()->removeDiscount(selectedVoucher);
                        break;
                    } 
                }
                
                if (!selectedVoucher) {
                    printMessage("Invalid voucher code!", 10, 27);
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
            int discountChoice = getValidatedInput<int>(
                "Choose a discount type (1 for 10% off, 2 for $5 off): ",
                [](const string& prompt) {
                    return InputChecker::checkInt(prompt, 10, 28, 1, 2);
                },
                10, 28
            );
            
            // Set discount value based on choice (10% for percentage, $5 for fixed amount)
            int discountValue = (DiscountType::PERCENTAGE == discountChoice) ? 10 : 5;

            // Create and add the new voucher
            shared_ptr<Discount> discount = DiscountService::getInstance()->createDiscount(customer->getUsername(),
                                         static_cast<DiscountType>(discountChoice), discountValue);
            // Notify the user about the new voucher
            string notify = (static_cast<DiscountType>(discountChoice) == DiscountType::PERCENTAGE) ? "10% off" : "$5 off";
            printMessage("New voucher created! Voucher code: " + discount->getCode() + ". " + notify + " on your next purchase.", 10, 29);
        }

        CustomerUI::displayOrderSuccessMessage();

    }

    //pauseScreen();
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
