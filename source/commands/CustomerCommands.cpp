#include "CustomerCommands.h"
#include "../ui/CustomerUI.h"
#include "../models/Music.h"
#include "../models/Order.h"
#include "../services/DiscountService.h"
#include "../services/MusicService.h"
#include "../services/CartService.h"
#include "../services/SalesRecordService.h"
#include "../services/OrderService.h"
#include "../ui/utils.h"
#include "../ui/InputChecker.h"
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
    printFrame(0, 0, 120, 30, LYELLOW);

    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    vector<Order> orders = OrderService::getInstance()->getAllOrders();

    // Get order history for the current customer
    vector<Order> orderHistory = OrderService::getInstance()->getUserOrders(customer->getUsername());
    
    string header = "purchaseHistory";
    printHeader(header, (120 - header.length()*2) / 2 - 31, 1, YELLOW);

    CustomerUI::displayPurchasedHistory(orderHistory);

    return true;
}

// ViewMusicCommand implementation
std::string ViewMusicCommand::getName() const {
    return "SEE MUSIC LIST";
}

bool ViewMusicCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30, LYELLOW);

    string header = "musicList";
    printHeader(header, (120 - header.length()*2) / 2 - 19, 1, YELLOW);

    vector<Music> items = MusicService::getInstance()->getAllMusic();

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
        printFrame(0, 0, 120, 30, LYELLOW);
        string header = "searchMusic";
        printHeader(header, (120 - header.length()*2) / 2 - 23, 1, YELLOW);
        
        printFrame(24, 10, 75, 3);
        printMessage("ENTER SEARCH CRITERIA (1 FOR NAME, 2 FOR ARTIST, 3 FOR GENRE): ", 26, 11);

        printFrameOptions(40, 13, 40, 1);
        ConsoleUI::gotoXY(42, 14);
        cout << "ENTER PASSWORD : ";

        ConsoleUI::setColor(YELLOW);
        // Get search criteria with validation
        int criteria = getValidatedInput<int>(
            "ENTER SEARCH CRITERIA (1 FOR NAME, 2 FOR ARTIST, 3 FOR GENRE): ",
            [](const string& prompt) {
                return InputChecker::checkInt(prompt, 26, 11, 1, 3);
            },
            26, 11
        );

        ConsoleUI::setColor(LYELLOW);
        // Get search keyword with validation
        string keyword = getValidatedInput<string>(
            "ENTER PASSWORD: ",
            [](const string& prompt) {
                return InputChecker::checkString(prompt, 42, 14);
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

        printRepeatMessage(107, 1, "CONTINUE", LYELLOW);
        printRepeatMessage(2, 1, "EXIT", LRED);
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
        printFrame(0, 0, 120, 30, LYELLOW);
        string header = "addToCart";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1, YELLOW);

        // Get all music items from the repository
        vector<Music> items = MusicService::getInstance()->getAllMusic();
        if (items.empty()) {
            printFrame(40, 14, 40, 3); 
            printMessage("NO ITEMS LEFT IN INVENTORY!", 45, 15);
            sleepScreen(1200);
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

        ConsoleUI::setColor(LYELLOW);
        // Get item ID with validation
        int itemID = getValidatedInput<int>(
            "ENTER ITEM ID : ",
            [&items](const string& prompt) {
                return InputChecker::checkInt(prompt, 9, 24, 1, items.size());
            },
            9, 24
        );

        ConsoleUI::setColor(LYELLOW);
        // Get quantity with validation
        int quantity = getValidatedInput<int>(
            "ENTER QUANTITY: ",
            [](const string& prompt) {
                return InputChecker::checkInt(prompt, 9, 26, 1, INT_MAX);
            },
            9, 26
        );

        // Add item to cart
        if (CartService::getInstance()->addItemToCart(cart, itemID, quantity)) {
            printFrame(49, 24, 66, 3, LGREEN); 
            printMessage("ADDED (" + to_string(quantity) + ") \"" + items[itemID - 1].getName() + "\" TO CART SUCCESSFULLY!", 55, 25, LGREEN);
        } else {
            printFrame(49, 24, 40, 3, LRED); 
            printMessage("FAILED TO ADD ITEM. NOT ENOUGH STOCK!", 51, 25, LRED);
            sleepScreen(1200);
        }

        printRepeatMessage(107, 1, "CONTINUE", LYELLOW);
        printRepeatMessage(2, 1, "EXIT",  LRED);
        char repeat = _getch();

        if (27 == repeat) {
            break;
        }
    }
    return true;
}

// ViewCurrentCartCommand implementation
ViewCurrentCartCommand::ViewCurrentCartCommand(Cart& c) : cart(c) {

}

std::string ViewCurrentCartCommand::getName() const {
    return "VIEW CURRENT CART";
}

bool ViewCurrentCartCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30, LYELLOW);
    string header = "currentCart";
    printHeader(header, (120 - header.length()*2) / 2 - 19, 1, YELLOW);

    CustomerUI::displayCart(cart.getItems(), 8);
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
        printFrame(0, 0, 120, 30, LYELLOW);
        string header = "removeItems";
        printHeader(header, (120 - header.length()*2) / 2 - 24, 1, YELLOW);

        // Get all music items from the repository
        vector<Music> items = MusicService::getInstance()->getAllMusic();

        if (cart.getItems().empty()) {
            printFrame(40, 14, 40, 3, LRED);
            printMessage("CART IS EMPTY!", 52, 15, LRED);
            sleepScreen(1200);
            return true;
        } else {
            CustomerUI::displayCart(cart.getItems(), 7);
            printFrame(0, 0, 120, 30, LYELLOW);
            printHeader(header, (120 - header.length()*2) / 2 - 24, 1, YELLOW);
        }

        printFrameOptions(7, 25, 40, 1);

        ConsoleUI::gotoXY(9, 26);
        cout << "ENTER ITEM ID TO REMOVE  : ";

        ConsoleUI::setColor(LYELLOW);
        // Get item ID to remove with validation
        int itemID = getValidatedInput<int>(
            "ENTER ITEM ID TO REMOVE: ",
            [this](const string& prompt) {
                return InputChecker::checkInt(prompt, 9, 26, 1, cart.getItems().size());
            },
            9, 26
        );

        // Remove item from cart
        if (CartService::getInstance()->removeItemFromCart(cart, itemID - 1)) {
            printFrame(49, 25, 40, 3, LGREEN); 
            printMessage("ITEM REMOVED SUCCESSFULLY!", 55, 26, LGREEN);
        } else {
            printFrame(49, 25, 40, 3, LRED); 
            printMessage("ERROR WHILE REMOVING THE ITEMS!", 50, 26, LRED);
        }

        printRepeatMessage(2, 1, "EXIT", LRED);
        printRepeatMessage(107, 1, "CONTINUE", LYELLOW);

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
    printFrame(0, 0, 120, 30, LYELLOW);
    string header = "checkOut";
    printHeader(header, (120 - header.length()*2) / 2 - 19, 1, YELLOW);

    Customer* customer = dynamic_cast<Customer*>(currentUser.get());

    // Get all orders and vouchers from the repository
    // vector<Order> orders = OrderService::getInstance()->getAllOrders();
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
        printFrame(0, 0, 120, 30, LYELLOW);
        printHeader(header, (120 - header.length()*2) / 2 - 19, 1, YELLOW);

        if (!validVouchers.empty()) {
            // Display available vouchers
            printFrame(25, 23, 70, 3);
            printMessage("DO YOU WANT TO USE A VOUCHER? (1 FOR YES, 2 FOR NO)  : ", 30, 24);

            ConsoleUI::setColor(LYELLOW);
            int useVoucher = getValidatedInput<int>(
                "DO YOU WANT TO USE A VOUCHER? (1 FOR YES, 2 FOR NO): ",
                [](const string& prompt) {
                    return InputChecker::checkInt(prompt, 30, 24, 1, 2);
                },
                30, 24
            );

            if (Agreement::YES == useVoucher) {
                clearScreen();
                printFrame(0, 0, 120, 30);
                printHeader(header, (120 - header.length()*2) / 2 - 19, 1);
                CustomerUI::displayVoucherList(validVouchers);
                // Get voucher code
                printFrameOptions(40, 23, 40, 1);

                ConsoleUI::gotoXY(42, 24);
                cout << "ENTER VOUCHER CODE  : ";

                ConsoleUI::setColor(LYELLOW);
                string voucherCode = getValidatedInput<string>(
                    "ENTER VOUCHER CODE: ",
                    [](const string& prompt) {
                        return InputChecker::checkString(prompt, 42, 24);
                    },
                    42, 24
                );
                
                // Find and apply the selected voucher
                for (const auto& voucher : validVouchers) {
                    if (voucher->getCode() == voucherCode) {
                        selectedVoucher = voucher;
                        
                        // Apply the discount to the total
                        total = DiscountService::getInstance()->applyDiscount(selectedVoucher, total);

                        printFrame(30, 26, 60, 3);
                        printMessage("VOUCHER APPLIED! NEW TOTAL: $" + to_string(total), 40, 27, YELLOW);
                        
                        // Remove the used voucher
                        DiscountService::getInstance()->removeDiscount(selectedVoucher);
                        break;
                    } 
                }
                
                if (!selectedVoucher) {
                    printFrame(40, 26, 40, 3, LRED);
                    printMessage("INVALID VOUCHER CODE!", 50, 27, LRED);
                    if (total <= 50) {
                        printFrameOptions(40, 23, 40, 1);
                        clearScreen(40, 23, 40, 3);
                        printFrame(40, 23, 40, 3);
                        ConsoleUI::setColor(YELLOW);
                        ConsoleUI::gotoXY(50, 24);
                        cout << char(175) << " TOTAL REVENUE: $" << total;
                    }
                }
                sleepScreen(1200);
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
            clearScreen();
            printFrame(0, 0, 120, 30);
            printHeader(header, (120 - header.length()*2) / 2 - 19, 1);

            CustomerUI::displayDiscountOptions();

            printFrameOptions(20, 19, 80, 1);

            ConsoleUI::gotoXY(30, 20);
            cout << "CHOOSE A DISCOUNT TYPE (1 FOR 10% OFF, 2 FOR $5 OFF)  : ";

            // Get discount type choice
            ConsoleUI::setColor(LYELLOW);
            int discountChoice = getValidatedInput<int>(
                "CHOOSE A DISCOUNT TYPE (1 FOR 10% OFF, 2 FOR $5 OFF): ",
                [](const string& prompt) {
                    return InputChecker::checkInt(prompt, 30, 20, 1, 2);
                },
                30, 20
            );
            
            // Set discount value based on choice (10% for percentage, $5 for fixed amount)
            int discountValue = (DiscountType::PERCENTAGE == discountChoice) ? 10 : 5;

            // Create and add the new voucher
            shared_ptr<Discount> discount = DiscountService::getInstance()->createDiscount(customer->getUsername(),
                                         static_cast<DiscountType>(discountChoice), discountValue);
            // Notify the user about the new voucher
            string notify = (static_cast<DiscountType>(discountChoice) == DiscountType::PERCENTAGE) ? "10% off" : "$5 off";

            printFrame(20, 22, 80, 3);
            printMessage("NEW VOUCHER CREATED! VOUCHER CODE: " + discount->getCode() + ". " + notify + " ON YOUR NEXT PURCHASE.", 23, 23, YELLOW);
            sleepScreen(1200);
        }
        clearScreen(106, 1, 13, 4);
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