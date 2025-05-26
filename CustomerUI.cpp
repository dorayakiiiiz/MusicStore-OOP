/**
 * @file CustomerUI.cpp
 * @brief Implementation file for the CustomerUI class
 * 
 * @details Contains implementations of all display functions and input collection
 *          methods for the customer interface
 */

#include "CustomerUI.h"
#include "utils.h"
#include <iomanip> 

// Displays a personalized welcome message for the customer
void CustomerUI::displayWelcomeMessage(const string& username) {
    printMessage("WELCOME " + username + " TO THE MUSIC STORE!", 10, 20);
}

// Displays the order history for a specific customer
// Shows all previous orders with details of purchased items and totals
void CustomerUI::displayPurchasedHistory(const vector<Order>& orders) {
    if (orders.empty()) {
        printFrame(40, 14, 40, 3); 
        printMessage("NO PURCHASE HISTORY FOUND!",  46, 15);
        printRepeatMessage(2, 1, "EXIT");   

        char key = _getch();

        if (27 == key) {
            return;
        }
    }

    int x = 7;
    int y = 13;
    int maxPerPage = 1;
    int width = 106;
    int totalItems = orders.size();
    int totalPages = totalItems;
    int currentPage = 0;

    vector<int> cols = {4, 47, 70, 82, 94};

    while (true) {
        int OrderIdx = currentPage * maxPerPage;

        //Xóa bảng cũ
        clearScreen(x, y, width, maxPerPage * 2 + 4); // xóa vùng tối đa
        // Xóa page 
        clearScreen(111, 28, 8, 1); 
        // Xóa vùng thông báo
        clearScreen(2, 1, 7, 4);
        // Xóa hiển thiện điều hướng
        clearScreen(2, 14, 1, 2);
        clearScreen(117, 14, 1, 2);

        printFrameOptions(x, 11, width, 1);
        ConsoleUI::gotoXY(x + 50, 12);
        cout << "ORDER " << OrderIdx + 1;

        const vector<Music>& purchasedItems = orders[OrderIdx].getPurchasedItems();
        int rows = purchasedItems.size() + 1;
        printFrameOptions(x, y, width, rows);

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + 1);
            std::cout << char(179); // │
            ConsoleUI::gotoXY(x + col, y);
            std::cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            std::cout << char(197); 
        }

        // In header
        ConsoleUI::gotoXY(x + 1, y + 1); std::cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); std::cout << "SONG NAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); std::cout << "ARTIST";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); std::cout << "QUANTITY";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); std::cout << "PRICE/UNIT";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); std::cout << "TOTAL";

        for (int i = 0; i < purchasedItems.size(); ++i) {
            int displayIdx = i + 1;
            int curY = y + displayIdx * 2 + 1;

            for (int col : cols) {
                ConsoleUI::gotoXY(x + col, curY);
                std::cout << char(179); // │
                ConsoleUI::gotoXY(x + col, curY + 1);
                std::cout << char(197); 
            }

            ConsoleUI::gotoXY(x + 1, curY); std::cout << i + 1;
            ConsoleUI::gotoXY(x + cols[0] + 1, curY); std::cout << purchasedItems[i].getName();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); std::cout << purchasedItems[i].getArtist();
            ConsoleUI::gotoXY(x + cols[2] + 1, curY); std::cout << purchasedItems[i].getQuantity();
            ConsoleUI::gotoXY(x + cols[3] + 1, curY); std::cout << purchasedItems[i].getPrice();
            ConsoleUI::gotoXY(x + cols[4] + 1, curY); std::cout << purchasedItems[i].getPrice() * purchasedItems[i].getQuantity();
        }

        printFrameOptions(x, y + rows * 2, width, 1);
        ConsoleUI::gotoXY(10, y + rows * 2 + 1);
        cout << "ORDER TOTAL: $" << orders[OrderIdx].getTotal();

        // Bottom border
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows * 2 - 1);
            std::cout << char(179); // │
            ConsoleUI::gotoXY(x + col, y + rows * 2);
            std::cout << char(193); 
        }

        ConsoleUI::gotoXY(x, y);
        cout << char(195);
        ConsoleUI::gotoXY(x, y + rows * 2);
        cout << char(195);
        ConsoleUI::gotoXY(x + 105, y);
        cout << char(180);
        ConsoleUI::gotoXY(x + 105, y + rows * 2);
        cout << char(180);


        // Hiển thị điều hướng trang
        ConsoleUI::gotoXY(111, 28);
        std::cout << "PAGE " << currentPage + 1 << "/" << totalPages;

        //pre page
        ConsoleUI::gotoXY(2, 15);
        std::cout << char(174);
        ConsoleUI::gotoXY(2, 14);
        std::cout << "A";

        //next page
        ConsoleUI::gotoXY(117, 15);
        std::cout << char(175);
        ConsoleUI::gotoXY(117, 14);
        std::cout << "D";

        printRepeatMessage(2, 1, "EXIT");   

        char key = _getch();

        if (27 == key) {
            break;
        }
        else if ((key == 'a' || key == 'A') && currentPage > 0) {
            --currentPage;
        } else if ((key == 'd' || key == 'D') && currentPage < totalPages - 1) {
            ++currentPage;
        }

    }
}

// Displays a formatted list of all available music items
void CustomerUI::displayMusicList(vector<Music>& items, int maxPerPage) {
    int x = 7;
    int y = 8;
    int width = 106;
    int totalItems = items.size();
    int totalPages = (totalItems + maxPerPage - 1) / maxPerPage;
    int currentPage = 0;

    vector<int> cols = {4, 47, 70, 82, 94};

    while (true) {
        int startIdx = currentPage * maxPerPage;
        int endIdx = (startIdx + maxPerPage > totalItems ? totalItems : startIdx + maxPerPage);
        int rows = endIdx - startIdx + 1; //

        //Xóa bảng cũ
        clearScreen(x, y, width, maxPerPage * 2 + 4); // xóa vùng tối đa
        // Xóa page 
        clearScreen(111, 28, 8, 1); 
        // Xóa vùng thông báo
        clearScreen(2, 1, 7, 4);
        clearScreen(107, 1, 11, 4);
        // Xóa hiển thiện điều hướng
        clearScreen(2, 14, 1, 2);
        clearScreen(117, 14, 1, 2);

        printFrameOptions(x, y, width, rows);

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + 1);
            std::cout << char(179); // │
            ConsoleUI::gotoXY(x + col, y);
            std::cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            std::cout << char(197); 
        }

        // In header
        ConsoleUI::gotoXY(x + 1, y + 1); std::cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); std::cout << "SONG NAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); std::cout << "ARTIST";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); std::cout << "GENRE";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); std::cout << "PRICE";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); std::cout << "QUANTITY";

        for (int i = startIdx; i < endIdx; ++i) {
            int displayIdx = i - startIdx + 1;
            int curY = y + displayIdx * 2 + 1;

            for (int col : cols) {
                ConsoleUI::gotoXY(x + col, curY);
                std::cout << char(179); // │
                ConsoleUI::gotoXY(x + col, curY + 1);
                std::cout << char(197); 
            }

            ConsoleUI::gotoXY(x + 1, curY); std::cout << i + 1;
            ConsoleUI::gotoXY(x + cols[0] + 1, curY); std::cout << items[i].getName();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); std::cout << items[i].getArtist();
            ConsoleUI::gotoXY(x + cols[2] + 1, curY); std::cout << items[i].getGenre();
            ConsoleUI::gotoXY(x + cols[3] + 1, curY); std::cout << items[i].getPrice();
            ConsoleUI::gotoXY(x + cols[4] + 1, curY); std::cout << items[i].getQuantity();
        }

        // Bottom border
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows * 2 - 1);
            std::cout << char(179); // │
            ConsoleUI::gotoXY(x + col, y + rows * 2);
            std::cout << char(193); 
        }

        // Hiển thị điều hướng trang
        ConsoleUI::gotoXY(111, 28);
        std::cout << "PAGE " << currentPage + 1 << "/" << totalPages;

        //pre page
        ConsoleUI::gotoXY(2, 15);
        std::cout << char(174);
        ConsoleUI::gotoXY(2, 14);
        std::cout << "A";

        //next page
        ConsoleUI::gotoXY(117, 15);
        std::cout << char(175);
        ConsoleUI::gotoXY(117, 14);
        std::cout << "D";

        // Đợi người dùng nhập phím
        if(8 == maxPerPage){
            printRepeatMessage(2, 1, "EXIT");    
        }
        else if (6 == maxPerPage){
            printRepeatMessage(107, 1, "ADD ITEM");
        }

        char key = _getch();

        if (27 == key && 8 == maxPerPage) {
            clearScreen();
            break;
        }
        else if (13 == key && 8 != maxPerPage){
            break;
        }
        else if ((key == 'a' || key == 'A') && currentPage > 0) {
            --currentPage;
        } else if ((key == 'd' || key == 'D') && currentPage < totalPages - 1) {
            ++currentPage;
        }

    }
}

// Displays the current items in the shopping cart
// Shows name, quantity, unit price and total price for each item
void CustomerUI::displayCart(const vector<Music>& items, int maxPerPage) {
    int x = 7;
    int y = 8;
    int width = 106;
    int totalItems = items.size();
    int totalPages = (totalItems + maxPerPage - 1) / maxPerPage;
    int currentPage = 0;

    vector<int> cols = {4, 47, 70, 82, 94};
    clearScreen();
    printFrame(0, 0, 120, 30);
    string header = "currentCart";
    printHeader(header, (120 - header.length()*2) / 2 - 24, 1);

    while (true) {
        int startIdx = currentPage * maxPerPage;
        int endIdx = (startIdx + maxPerPage > totalItems ? totalItems : startIdx + maxPerPage);
        int rows = endIdx - startIdx + 1; //

        //Xóa bảng cũ
        clearScreen(x, y, width, maxPerPage * 2 + 4); // xóa vùng tối đa
        // Xóa page 
        clearScreen(111, 28, 8, 1); 
        // Xóa vùng thông báo
        clearScreen(2, 1, 7, 4);
        clearScreen(109, 1, 9, 4);
        // Xóa hiển thiện điều hướng
        clearScreen(2, 14, 1, 2);
        clearScreen(117, 14, 1, 2);

        printFrameOptions(x, y, width, rows);

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + 1);
            std::cout << char(179); // │
            ConsoleUI::gotoXY(x + col, y);
            std::cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            std::cout << char(197); 
        }

        // In header
        ConsoleUI::gotoXY(x + 1, y + 1); std::cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); std::cout << "SONG NAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); std::cout << "ARTIST";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); std::cout << "PRICE/UNIT";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); std::cout << "QUANTITY";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); std::cout << "TOTAL";

        for (int i = startIdx; i < endIdx; ++i) {
            int displayIdx = i - startIdx + 1;
            int curY = y + displayIdx * 2 + 1;

            for (int col : cols) {
                ConsoleUI::gotoXY(x + col, curY);
                std::cout << char(179); // │
                ConsoleUI::gotoXY(x + col, curY + 1);
                std::cout << char(197); 
            }

            ConsoleUI::gotoXY(x + 1, curY); std::cout << i + 1;
            ConsoleUI::gotoXY(x + cols[0] + 1, curY); std::cout << items[i].getName();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); std::cout << items[i].getArtist();
            ConsoleUI::gotoXY(x + cols[2] + 1, curY); std::cout << items[i].getPrice();
            ConsoleUI::gotoXY(x + cols[3] + 1, curY); std::cout << items[i].getQuantity();
            ConsoleUI::gotoXY(x + cols[4] + 1, curY); std::cout << items[i].getPrice() * items[i].getQuantity();
        }

        // Bottom border
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows * 2 - 1);
            std::cout << char(179); // │
            ConsoleUI::gotoXY(x + col, y + rows * 2);
            std::cout << char(193); 
        }

        // Hiển thị điều hướng trang
        ConsoleUI::gotoXY(111, 28);
        std::cout << "PAGE " << currentPage + 1 << "/" << totalPages;

        //pre page
        ConsoleUI::gotoXY(2, 15);
        std::cout << char(174);
        ConsoleUI::gotoXY(2, 14);
        std::cout << "A";

        //next page
        ConsoleUI::gotoXY(117, 15);
        std::cout << char(175);
        ConsoleUI::gotoXY(117, 14);
        std::cout << "D";

        // Đợi người dùng nhập phím
        if(8 == maxPerPage){
            printRepeatMessage(2, 1, "EXIT");    
        }
        else if (7 == maxPerPage){
            printRepeatMessage(109, 1, "REMOVE");
        }

        char key = _getch();

        if (27 == key && 8 == maxPerPage) {
            clearScreen();
            break;
        }
        else if (13 == key && 8 != maxPerPage){
            break;
        }
        else if ((key == 'a' || key == 'A') && currentPage > 0) {
            --currentPage;
        } else if ((key == 'd' || key == 'D') && currentPage < totalPages - 1) {
            ++currentPage;
        }

    }
}

// Displays a message when no search results are found
void CustomerUI::displayNoResultsMessage() {
    printFrame(40, 14, 40, 3);
    printMessage("NO RESULTS FOUND!",  48, 155);
}

// Displays search results from a music search operation
void CustomerUI::displaySearchResults(vector<Music>& results) {
    displayMusicList(results, 8);
}

// Displays a message when attempting to checkout with an empty cart
void CustomerUI::displayEmptyCartMessage() {
    printFrame(30, 14, 50, 3);
    printMessage("CART IS EMPTY! PLEASE ADD ITEMS TO CART BEFORE CHECKING OUT.",  40, 15);
}

// Displays order details before confirming checkout
// Shows username, list of items, and total price
void CustomerUI::displayOrderDetails(const string& username, const vector<Music>& items, float total) {
    printMessage("Your order details: ",  20, 15);
    printMessage("Username: " + username, 20, 16);
    printMessage("Purchased items: ", 20, 17);
    displayCart(items, 8);
    printMessage("Total: $" + std::to_string(total), 20, 18);
}

// Displays the list of available discount vouchers for the customer
void CustomerUI::displayVoucherList(const vector<shared_ptr<Discount>>& vouchers) {
    printMessage("You have the following vouchers available: ", 20, 15);
    for (int i = 0; i < vouchers.size(); ++i) {
        cout << '\t' << i + 1 << ". " << vouchers[i]->toString() << '\n';
    }
}

// Displays discount options after a large purchase (over $50)
// Shows available discount types the customer can choose
void CustomerUI::displayDiscountOptions() {
    printMessage("Congratulations! As the total is over $50, you will receive a discount voucher for your next purchase", 20, 20);
    printMessage("What type of discount would you like to apply?", 20, 21);
    printMessage("1. Percentage discount", 20, 22);
    printMessage("2. Fixed amount discount", 20, 23);
}

// Displays a success message after completing an order
void CustomerUI::displayOrderSuccessMessage() {
    printMessage("Order placed successfully! Thank you for your purchase!", 20, 20);
}

// Displays a message when the customer logs out
void CustomerUI::displayLogoutMessage() {
    printMessage("You have logged out successfully!", 20, 20);
}

// Displays a warning when attempting to log out with items still in cart
void CustomerUI::displayCartWarningMessage() {
    printMessage("You have items in your cart! Please check out before logging out.", 20, 20);
}

// Displays a message for invalid menu choices
void CustomerUI::displayInvalidChoiceMessage() {
    printMessage("Invalid choice! Please try again.", 20, 20);
}
