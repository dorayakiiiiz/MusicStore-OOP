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
    CustomerUI::displayPurchasedHistory(orderHistory);

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
    if (items.empty()) {
        printFrame(30, 14, 60, 3); 
        printMessage("NO ITEMS FOUND!", 50, 15);
        printRepeatMessage(2, 1, "EXIT");

        char repeat = _getch();

        if (27 == repeat) {
            return true;
        }
    }
    CustomerUI::displayMusicList(items, 8);

    return true;
}

// SearchMusicCommand implementation
string SearchMusicCommand::getName() const {
    return "FIND ITEM";
}

bool SearchMusicCommand::execute() {
    // get all music items from the repository
    vector<Music> items = MusicService::getInstance()->getAllMusic();

    while (true) {
        clearScreen();
        printFrame(0, 0, 120, 30);
        string header = "searchMusic";
        printHeader(header, (120 - header.length()*2) / 2 - 23, 1);
        
        printFrame(24, 10, 75, 3);
        printMessage("ENTER SEARCH CRITERIA (1 FOR NAME, 2 FOR ARTIST, 3 FOR GENRE): ", 26, 11);

        printFrameOptions(40, 13, 40, 1);
        ConsoleUI::gotoXY(42, 14);
        cout << "ENTER PASSWORD : ";

        // Get search criteria with validation
        int criteria = getValidatedInput<int>(
            "ENTER SEARCH CRITERIA (1 FOR NAME, 2 FOR ARTIST, 3 FOR GENRE): ",
            [](const string& prompt) {
                return InputChecker::validateInt(prompt, 26, 11, 1, 3);
            },
            26, 11
        );

        // Get search keyword with validation
        string keyword = getValidatedInput<string>(
            "ENTER PASSWORD: ",
            [](const string& prompt) {
                return InputChecker::validateString(prompt, 42, 14);
            },
            42, 14
        );


        // Perform search and display results
        vector<Music> results = MusicService::getInstance()->searchMusic(items, static_cast<SearchType>(criteria), keyword);

        if (results.empty()) {
            CustomerUI::displayNoResultsMessage();
        } else {
            CustomerUI::displaySearchResults(results);

            printFrame(0, 0, 120, 30);
            printHeader(header, (120 - header.length()*2) / 2 - 23, 1);

            printFrame(24, 10, 75, 3);
            printMessage("ENTER SEARCH CRITERIA (1 FOR NAME, 2 FOR ARTIST, 3 FOR GENRE): ", 26, 11);

            printFrameOptions(40, 13, 40, 1);
            ConsoleUI::gotoXY(42, 14);
            cout << "ENTER PASSWORD : ";
        }

        printRepeatMessage(107, 1, "CONTINUE");
        printRepeatMessage(2, 1, "EXIT");
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
    while (true) {
        clearScreen();
        printFrame(0, 0, 120, 30);
        string header = "addToCart";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1);

        // Get all music items from the repository
        vector<Music> items = MusicService::getInstance()->getAllMusic();
        if (items.empty()) {
            printFrame(40, 14, 40, 3); 
            printMessage("NO ITEMS LEFT IN INVENTORY!", 45, 15);
            return true;
        }


        // Display current music list
        CustomerUI::displayMusicList(items, 6);
        // Get item ID and quantity from user

        printFrameOptions(7, 23, 40, 2);

        ConsoleUI::gotoXY(9, 24);
        cout << "ENTER ITEM ID   : ";
        ConsoleUI::gotoXY(9, 26);
        cout << "ENTER QUANTITY  : ";

        // Get item ID with validation
        int itemID = getValidatedInput<int>(
            "ENTER ITEM ID : ",
            [&items](const string& prompt) {
                return InputChecker::validateInt(prompt, 9, 24, 1, items.size());
            },
            9, 24
        );

        // Get quantity with validation
        int quantity = getValidatedInput<int>(
            "ENTER QUANTITY: ",
            [](const string& prompt) {
                return InputChecker::validateInt(prompt, 9, 26, 1, INT_MAX);
            },
            9, 26
        );

        // Add item to cart
        if (CartService::getInstance()->addItemToCart(cart, itemID, quantity)) {
            printFrame(49, 24, 46, 3); 
            printMessage("ADDED " + to_string(quantity) + " " + items[itemID - 1].getName() + " TO CART SUCCESSFULLY!", 51, 25);
        } else {
            printFrame(49, 24, 40, 3); 
            printMessage("FAILED TO ADD ITEM. NOT ENOUGH STOCK!", 60, 25);
            sleepScreen(1200);
        }

        printRepeatMessage(107, 1, "CONTINUE");
        printRepeatMessage(2, 1, "EXIT");
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
    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30);
        string header = "removeItems";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1);

        // Get all music items from the repository
        vector<Music> items = MusicService::getInstance()->getAllMusic();

        if (cart.getItems().empty()) {
            printFrame(40, 14, 40, 3);
            printMessage("CART IS EMPTY!", 55, 15);

            printRepeatMessage(2, 1, "EXIT");
            char repeat = _getch();
            if (27 == repeat) {
                break;
        }
        } else {
            CustomerUI::displayCart(cart.getItems(), 7);
            printFrame(0, 0, 120, 30);
            printHeader(header, (120 - header.length()*2) / 2 - 24, 1);
        }

        printFrameOptions(7, 25, 40, 1);

        ConsoleUI::gotoXY(9, 26);
        cout << "ENTER ITEM ID TO REMOVE  : ";


        // Get item ID to remove with validation
        int itemID = getValidatedInput<int>(
            "ENTER ITEM ID TO REMOVE: ",
            [this](const string& prompt) {
                return InputChecker::validateInt(prompt, 9, 26, 1, cart.getItems().size());
            },
            9, 26
        );

        // Remove item from cart
        if (CartService::getInstance()->removeItemFromCart(cart, itemID - 1)) {
            printFrame(49, 25, 40, 3); 
            printMessage("ITEM REMOVED SUCCESSFULLY!", 55, 26);
        } else {
            printFrame(49, 25, 40, 3); 
            printMessage("ERROR WHILE REMOVING THE ITEMS!", 50, 26);
        }

        printRepeatMessage(2, 1, "EXIT");
        printRepeatMessage(107, 1, "CONTINUE");

        char repeat = _getch();
        if (27 == repeat) {
            break;
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
                    return InputChecker::validateInt(prompt, 10, 24, 1, 2);
                },
                10, 24
            );

            if (Agreement::YES == useVoucher) {
                // Get voucher code
                string voucherCode = getValidatedInput<string>(
                    "Enter voucher code: ",
                    [](const string& prompt) {
                        return InputChecker::validateString(prompt, 10, 25);
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
                    return InputChecker::validateInt(prompt, 10, 28, 1, 2);
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

    printRepeatMessage(2, 1, "EXIT");

    char repeat = _getch();
    if (27 == repeat) {
        return true;
    }
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
