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
    printMessage("WELCOME " + username + " TO THE MUSIC STORE!", 10, 20, LGREEN);
}

// Displays the order history for a specific customer
// Shows all previous orders with details of purchased items and totals
void CustomerUI::displayPurchasedHistory(const vector<Order>& orders) {
    if (orders.empty()) {
        printFrame(40, 14, 40, 3, LRED); 
        printMessage("NO PURCHASE HISTORY FOUND!",  46, 15, LRED);
        sleepScreen(1200);
        return;
    }

    int x = 15;
    int y = 12;
    int maxPerPage = 1;
    int width = 90;
    int totalItems = orders.size();
    int totalPages = totalItems;
    int currentPage = 0;

    vector<int> cols = {4, 32, 54, 66, 78};

    while (true) {
        int OrderIdx = currentPage * maxPerPage;

        clearScreen(1, 12, 118, 17); 

        printFrameOptions(x, 10, width, 1);
        ConsoleUI::gotoXY(x + 41, 11);
        ConsoleUI::setColor(AQUA);
        cout << "ORDER " << OrderIdx + 1;
        ConsoleUI::setColor(WHITE);

        const vector<Music>& purchasedItems = orders[OrderIdx].getPurchasedItems();
        int rows = purchasedItems.size() + 1;
        printFrameOptions(x, y, width, rows);

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y);
            cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            cout << char(197); 
        }

        ConsoleUI::setColor(LYELLOW);
        ConsoleUI::gotoXY(x + 1, y + 1); 
        cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); 
        cout << "SONG NAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); 
        cout << "ARTIST";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); 
        cout << "QUANTITY";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); 
        cout << "PRICE/UNIT";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); 
        cout << "TOTAL";
        ConsoleUI::setColor(WHITE);

        for (int i = 0; i < purchasedItems.size(); ++i) {
            int displayIdx = i + 1;
            int curY = y + displayIdx * 2 + 1;

            for (int col : cols) {
                ConsoleUI::gotoXY(x + col, curY);
                cout << char(179);
                ConsoleUI::gotoXY(x + col, curY + 1);
                cout << char(197); 
            }

            ConsoleUI::gotoXY(x + 1, curY); 
            cout << i + 1;
            ConsoleUI::gotoXY(x + cols[0] + 1, curY); 
            cout << purchasedItems[i].getName();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); 
            cout << purchasedItems[i].getArtist();
            ConsoleUI::gotoXY(x + cols[2] + 1, curY); 
            cout << purchasedItems[i].getQuantity();
            ConsoleUI::gotoXY(x + cols[3] + 1, curY); 
            cout << purchasedItems[i].getPrice();
            ConsoleUI::gotoXY(x + cols[4] + 1, curY); 
            cout << purchasedItems[i].getPrice() * purchasedItems[i].getQuantity();
        }

        printFrameOptions(x, y + rows * 2, width, 1);
        ConsoleUI::gotoXY(17, y + rows * 2 + 1);
        ConsoleUI::setColor(Color::AQUA);
        cout << "ORDER TOTAL: $" << orders[OrderIdx].getTotal();
        ConsoleUI::setColor(Color::WHITE);

        // Bottom border
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows * 2 - 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y + rows * 2);
            cout << char(193); 
        }

        ConsoleUI::gotoXY(x, y);
        cout << char(195);
        ConsoleUI::gotoXY(x, y + rows * 2);
        cout << char(195);
        ConsoleUI::gotoXY(x + 89, y);
        cout << char(180);
        ConsoleUI::gotoXY(x + 89, y + rows * 2);
        cout << char(180);


        // Hiển thị điều hướng trang
        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(111 - totalPages/10, 28);
        cout << "PAGE " << currentPage + 1 << "/" << totalPages;

        //pre page
        ConsoleUI::gotoXY(2, 15);
        cout << char(174);
        ConsoleUI::gotoXY(2, 14);
        cout << "A";

        //next page
        ConsoleUI::gotoXY(117, 15);
        cout << char(175);
        ConsoleUI::gotoXY(117, 14);
        cout << "D";
        ConsoleUI::setColor(WHITE);

        if (0 == currentPage) {
            clearScreen(2, 14, 1, 2);
        } 
        if (currentPage == totalPages - 1) {
            clearScreen(117, 14, 1, 2);
        }

        printRepeatMessage(2, 1, "EXIT", LRED);   

        char key = _getch();

        if (27 == key) {
            break;
        }
        else if (('a' == key || 'A' == key) 
                && currentPage > 0) {
            --currentPage;
        } else if (('d' == key || 'D' == key) 
                && currentPage < totalPages - 1) {
            ++currentPage;
        }
    }
}

// Displays a formatted list of all available music items
void CustomerUI::displayMusicList(vector<Music>& items, int maxPerPage) {
    if (items.empty()) {
        printFrame(30, 20, 60, 3, LRED); 
        printMessage("NO ITEMS FOUND!", 50, 15, LRED);
        sleepScreen(1200);
        return;
    }

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
        int rows = endIdx - startIdx + 1; 

        clearScreen(1, 8, 118, 21); 

        printFrameOptions(x, y, width, rows);

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y);
            cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            cout << char(197); 
        }

        // In header
        ConsoleUI::setColor(LYELLOW);
        ConsoleUI::gotoXY(x + 1, y + 1); 
        cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); 
        cout << "SONG NAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); 
        cout << "ARTIST";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); 
        cout << "GENRE";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); 
        cout << "PRICE";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); 
        cout << "QUANTITY";
        ConsoleUI::setColor(WHITE);

        for (int i = startIdx; i < endIdx; ++i) {
            int displayIdx = i - startIdx + 1;
            int curY = y + displayIdx * 2 + 1;

            for (int col : cols) {
                ConsoleUI::gotoXY(x + col, curY);
                cout << char(179); 
                ConsoleUI::gotoXY(x + col, curY + 1);
                cout << char(197); 
            }

            ConsoleUI::gotoXY(x + 1, curY); 
            cout << i + 1;
            ConsoleUI::gotoXY(x + cols[0] + 1, curY); 
            cout << items[i].getName();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); 
            cout << items[i].getArtist();
            ConsoleUI::gotoXY(x + cols[2] + 1, curY); 
            cout << items[i].getGenre();
            ConsoleUI::gotoXY(x + cols[3] + 1, curY); 
            cout << items[i].getPrice();
            ConsoleUI::gotoXY(x + cols[4] + 1, curY); 
            cout << items[i].getQuantity();
        }

        // Bottom border
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows * 2 - 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y + rows * 2);
            cout << char(193); 
        }

        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(111 - totalPages / 10, 28);
        cout << "PAGE " << currentPage + 1 << "/" << totalPages;

        //pre page
        ConsoleUI::gotoXY(2, 15);
        cout << char(174);
        ConsoleUI::gotoXY(2, 14);
        cout << "A";

        //next page
        ConsoleUI::gotoXY(117, 15);
        cout << char(175);
        ConsoleUI::gotoXY(117, 14);
        cout << "D";
        ConsoleUI::setColor(Color::WHITE);

        if (0 == currentPage) {
            clearScreen(2, 14, 1, 2);
        } 
        if (currentPage == totalPages - 1) {
            clearScreen(117, 14, 1, 2);
        }

        if(8 == maxPerPage){
            printRepeatMessage(2, 1, "EXIT", LRED);    
        }
        else if (6 == maxPerPage){
            printRepeatMessage(108, 1, "ADD ITEM", LBLUE);
        }

        char key = _getch();

        if (27 == key && 8 == maxPerPage) {
            clearScreen();
            break;
        }
        else if (13 == key && 8 != maxPerPage){
            break;
        }
        else if (('a' == key|| 'A' == key) 
                && currentPage > 0) {
            --currentPage;
        } else if (('d' == key || 'D' == key) 
                && currentPage < totalPages - 1) {
            ++currentPage;
        }

    }
}

// Displays the current items in the shopping cart
// Shows name, quantity, unit price and total price for each item
void CustomerUI::displayCart(const vector<Music>& items, int maxPerPage) {
    if (items.empty()) {
        printFrame(40, 14, 40, 3, LRED);
        printMessage("CART IS EMPTY!", 52, 15, LRED);
        sleepScreen(1200);
        return;
    }

    int x = 7;
    int y = 8;
    int width = 106;
    int totalItems = items.size();
    int totalPages = (totalItems + maxPerPage - 1) / maxPerPage;
    int currentPage = 0;

    vector<int> cols = {4, 47, 70, 82, 94};
    clearScreen();
    printFrame(0, 0, 120, 30, LYELLOW);
    string header = "currentCart";
    printHeader(header, (120 - header.length()*2) / 2 - 24, 1, YELLOW);

    while (true) {
        int startIdx = currentPage * maxPerPage;
        int endIdx = (startIdx + maxPerPage > totalItems ? totalItems : startIdx + maxPerPage);
        int rows = endIdx - startIdx + 1; 

        clearScreen(1, 8, 118, 21); 

        printFrameOptions(x, y, width, rows);

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y);
            cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            cout << char(197); 
        }

        ConsoleUI::setColor(LYELLOW);
        ConsoleUI::gotoXY(x + 1, y + 1);
        cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); 
        cout << "SONG NAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); 
        cout << "ARTIST";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); 
        cout << "PRICE/UNIT";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); 
        cout << "QUANTITY";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); 
        cout << "TOTAL";
        ConsoleUI::setColor(Color::WHITE);

        for (int i = startIdx; i < endIdx; ++i) {
            int displayIdx = i - startIdx + 1;
            int curY = y + displayIdx * 2 + 1;

            for (int col : cols) {
                ConsoleUI::gotoXY(x + col, curY);
                cout << char(179); 
                ConsoleUI::gotoXY(x + col, curY + 1);
                cout << char(197); 
            }

            ConsoleUI::gotoXY(x + 1, curY); 
            cout << i + 1;
            ConsoleUI::gotoXY(x + cols[0] + 1, curY); 
            cout << items[i].getName();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); 
            cout << items[i].getArtist();
            ConsoleUI::gotoXY(x + cols[2] + 1, curY); 
            cout << items[i].getPrice();
            ConsoleUI::gotoXY(x + cols[3] + 1, curY); 
            cout << items[i].getQuantity();
            ConsoleUI::gotoXY(x + cols[4] + 1, curY); 
            cout << items[i].getPrice() * items[i].getQuantity();
        }

        // Bottom border
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows * 2 - 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y + rows * 2);
            cout << char(193); 
        }

        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(111 - totalPages / 10, 28);
        cout << "PAGE " << currentPage + 1 << "/" << totalPages;

        //pre page
        ConsoleUI::gotoXY(2, 15);
        cout << char(174);
        ConsoleUI::gotoXY(2, 14);
        cout << "A";

        //next page
        ConsoleUI::gotoXY(117, 15);
        cout << char(175);
        ConsoleUI::gotoXY(117, 14);
        cout << "D";
        ConsoleUI::setColor(Color::WHITE);

        if (0 == currentPage) {
            clearScreen(2, 14, 1, 2);
        } 
        if (currentPage == totalPages - 1) {
            clearScreen(117, 14, 1, 2);
        }

        if(8 == maxPerPage){
            printRepeatMessage(2, 1, "EXIT", LRED);   
        }
        else if (7 == maxPerPage){
            printRepeatMessage(109, 1, "REMOVE", LBLUE);
        }
        else {
            printRepeatMessage(106, 1, "CHECK OUT", LBLUE);
        }

        char key = _getch();

        if (27 == key && 8 == maxPerPage) {
            clearScreen();
            break;
        }
        else if (13 == key && 8 != maxPerPage){
            clearScreen(106, 1, 12, 4);
            break;
        }
        else if (('a' == key || 'A' == key) 
                && currentPage > 0) {
            --currentPage;
        } else if (('d' == key || 'D' == key) 
                && currentPage < totalPages - 1) {
            ++currentPage;
        }

    }
}

// Displays a message when no search results are found
void CustomerUI::displayNoResultsMessage() {
    printFrame(40, 14, 40, 3, LRED);
    printMessage("NO RESULTS FOUND!",  48, 15, LRED);
}

// Displays search results from a music search operation
void CustomerUI::displaySearchResults(vector<Music>& results) {
    displayMusicList(results, 8);
}

// Displays a message when attempting to checkout with an empty cart
void CustomerUI::displayEmptyCartMessage() {
    printFrame(29, 14, 65, 3, LRED);
    printMessage("CART IS EMPTY! PLEASE ADD ITEMS TO CART BEFORE CHECKING OUT.",  31, 15, LRED);
}

// Displays order details before confirming checkout
// Shows username, list of items, and total price
void CustomerUI::displayOrderDetails(const string& username, const vector<Music>& items, float total) {
    displayCart(items, 6);
    printFrame(40, 23, 40, 3, LYELLOW);
    ConsoleUI::gotoXY(50, 24);
    ConsoleUI::setColor(AQUA);
    cout << "TOTAL REVENUE: $" << total;
    ConsoleUI::setColor(WHITE);
    sleepScreen(1200);
    clearScreen(1, 1, 105, 5);
}

// Displays the list of available discount vouchers for the customer
void CustomerUI::displayVoucherList(const vector<shared_ptr<Discount>>& vouchers) {
    int x = 30;
    int y = 10;
    int width = 60;
    int maxPerPage = 4;
    int totalItems = vouchers.size();
    int totalPages = (totalItems + maxPerPage - 1) / maxPerPage;
    int currentPage = 0;

    printFrame(30, 7, 60, 3, LYELLOW);
    ConsoleUI::gotoXY(38, 8);
    ConsoleUI::setColor(LGREEN);
    cout << "YOU HAVE THE FOLLOWING VOUCHERS AVAILABLE";
    ConsoleUI::setColor(WHITE);

    while (true) {
        int startIdx = currentPage * maxPerPage;
        int endIdx = (startIdx + maxPerPage > totalItems ? totalItems : startIdx + maxPerPage);
        int rows = endIdx - startIdx + 1; 

        clearScreen(x, y, width, maxPerPage * 2 + 4);
        clearScreen(111, 28, 8, 1); 

        printFrameOptions(x, y, width, rows);

        ConsoleUI::gotoXY(x + 5, y + 1);
        cout << char(179);
        ConsoleUI::gotoXY(x + 5, y);
        cout << char(194); 
        ConsoleUI::gotoXY(x + 5, y + 2);
        cout << char(197); 
        
        ConsoleUI::setColor(LYELLOW);
        ConsoleUI::gotoXY(x + 1, y + 1);
        cout << "ID";
        ConsoleUI::gotoXY(x + 6, y + 1);
        cout << "VOUCHER";
        ConsoleUI::setColor(WHITE);

        for (int i = startIdx; i < endIdx; ++i) {
            int displayIdx = i - startIdx + 1;
            int curY = y + displayIdx * 2 + 1;
            
            ConsoleUI::gotoXY(x + 5, curY);
            cout << char(179); 
            ConsoleUI::gotoXY(x + 5, curY + 1);
            cout << char(197); 

            ConsoleUI::gotoXY(x + 1, curY); 
            cout << i + 1;
            ConsoleUI::gotoXY(x + 6, curY); 
            cout << vouchers[i]->toString();
        }

        ConsoleUI::gotoXY(x + 5, y + rows*2 - 1);
        cout << char(179); 
        ConsoleUI::gotoXY(x + 5, y + rows*2);
        cout << char(193); 
        

        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(111, 28);
        cout << "PAGE " << currentPage + 1 << "/" << totalPages;

        //pre page
        ConsoleUI::gotoXY(2, 15);
        cout << char(174);
        ConsoleUI::gotoXY(2, 14);
        cout << "A";

        //next page
        ConsoleUI::gotoXY(117, 15);
        cout << char(175);
        ConsoleUI::gotoXY(117, 14);
        cout << "D";
        ConsoleUI::setColor(Color::WHITE);

        if (0 == currentPage) {
            clearScreen(2, 14, 1, 2);
        } 
        if (currentPage == totalPages - 1) {
            clearScreen(117, 14, 1, 2);
        }

        printRepeatMessage(109, 1, "SELECT", LBLUE);

        char key = _getch();
        if (13 == key){
            break;
        }
        else if (('a' == key|| 'A' == key) 
                && currentPage > 0) {
            --currentPage;
        } else if (('d' == key || 'D' == key) 
                && currentPage < totalPages - 1) {
            ++currentPage;
        }
    }
}

// Displays discount options after a large purchase (over $50)
// Shows available discount types the customer can choose
void CustomerUI::displayDiscountOptions() {
    printFrame(7, 8, 107, 9, LYELLOW);
    ConsoleUI::gotoXY(9, 9);
    ConsoleUI::setColor(LBLUE);
    cout << "CONGRATULATIONS! AS THE TOTAL IS OVER $50, YOU WILL RECEIVE A DISCOUNT VOUCHER FOR YOUR NEXT PURCHASE";
    ConsoleUI::gotoXY(9, 11);
    cout << "WHAT TYPE OF DISCOUNT WOULD YOU LIKE TO APPLY?";
    ConsoleUI::gotoXY(11, 13);
    ConsoleUI::setColor(AQUA);
    cout << "1. PERCENTAGE DISCOUNT";
    ConsoleUI::gotoXY(11, 15);
    cout << "2. FIXED AMOUNT DISCOUNT";
    ConsoleUI::gotoXY(11, 17);
    ConsoleUI::setColor(WHITE);
}

// Displays a success message after completing an order
void CustomerUI::displayOrderSuccessMessage() {
    printFrame(30, 26, 60, 3, LGREEN);
    ConsoleUI::gotoXY(32, 27);
    ConsoleUI::setColor(LGREEN);
    cout << "ORDER PLACED SUCCESSFULLY! THANK YOU FOR YOUR PURCHASE!";
    ConsoleUI::setColor(WHITE);
}

// Displays a message when the customer logs out
void CustomerUI::displayLogoutMessage() {
    printFrame(5, 24, 50, 5, LGREEN);
    ConsoleUI::gotoXY(14, 26);
    ConsoleUI::setColor(LGREEN);
    cout << "YOU HAVE LOGGED OUT SUCCESSFULLY!";
    ConsoleUI::setColor(WHITE);
    sleepScreen(1200);
}

// Displays a warning when attempting to log out with items still in cart
void CustomerUI::displayCartWarningMessage() {
    printFrame(5, 23, 50, 6, LRED);
    ConsoleUI::gotoXY(12, 25);
    ConsoleUI::setColor(LRED);
    cout << "   YOU HAVE ITEMS IN YOUR CART!";
    ConsoleUI::gotoXY(12, 26);
    cout << "PLEASE CHECK OUT BEFORE LOGGING OUT.";
    ConsoleUI::setColor(WHITE);
    sleepScreen(1200);
}