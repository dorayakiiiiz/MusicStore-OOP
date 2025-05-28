/**
 * @file AdminUI.cpp
 * @brief Implementation file for the AdminUI class
 * 
 * @details Contains implementations of all display functions and input collection
 *          methods for the administrator interface
 */

#include "AdminUI.h"
#include "utils.h"
#include "ConsoleUI.h"
#include "InputChecker.h"
#include <conio.h>
#include <windows.h>

using std::cout, std::cin, std::vector, std::string;

// Displays a welcome message for the admin with their username
void AdminUI::displayWelcomeMessage(const string& username) {
    printMessage("WELCOME " + username + " TO THE ADMIN MENU!", 10, 20, LGREEN);
}

// Displays a formatted list of all music items in inventory
// Shows ID, name, artist, genre, price and quantity for each item
void AdminUI::displayMusicList(vector<Music>& items, int maxPerPage) {
    if (items.empty()) {
        printFrame(30, 14, 60, 3, LRED); 
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
            std::cout << char(179); 
            ConsoleUI::gotoXY(x + col, y);
            std::cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            std::cout << char(197); 
        }

        // In header
        ConsoleUI::setColor(AQUA);
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

        ConsoleUI::setColor(LYELLOW);
        // Hiển thị điều hướng trang
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
        ConsoleUI::setColor(WHITE);

        if (0 == currentPage) {
            clearScreen(2, 14, 1, 2);
        } 
        if (totalPages - 1 == currentPage) {
            clearScreen(117, 14, 1, 2);
        }

        if(8 == maxPerPage){
            printRepeatMessage(2, 1, "EXIT", LRED);    
        }
        else if (7 == maxPerPage){
            printRepeatMessage(109, 1, "REMOVE", YELLOW);
        }
        else{
            printRepeatMessage(109, 1, "UPDATE", YELLOW);
        }

        char key = _getch();

        if (27 == key && 8 == maxPerPage) {
            break;
        }
        else if (13 == key && 8 != maxPerPage){
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

// Displays a formatted list of all registered users
// Shows ID, username, and role for each user
void AdminUI::displayUserList(const vector<shared_ptr<User>>& users, int maxPerPage) {
    int x = 20;
    int y = 7.5;
    int width = 80;
    int totalItems = users.size();
    int totalPages = (totalItems + maxPerPage - 1) / maxPerPage;
    int currentPage = 0;

    vector<int> cols = {5, 50};

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
            //In header
        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(x + 1, y + 1);
        cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1);
        cout << "USERNAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1);
        cout << "ROLE";
        ConsoleUI::setColor(WHITE);

        for (int i = startIdx; i < endIdx; ++i) {
            int displayIdx = i - startIdx + 1;
            int curY = y + displayIdx * 2 + 1;

            for (int col : cols) {
                ConsoleUI::gotoXY(x + col, curY);
                std::cout << char(179); 
                ConsoleUI::gotoXY(x + col, curY + 1);
                std::cout << char(197); 
            }

            ConsoleUI::gotoXY(x + 1, curY); 
            cout << i + 1;
            ConsoleUI::gotoXY(x + cols[0] + 1, curY);
            cout << users[i]->getUsername();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); 
            cout << (Role::ADMIN == users[i]->getRole() ? "Admin" : "Customer");
        }

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows*2 - 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y + rows*2);
            cout << char(193); 
        }

        ConsoleUI::setColor(LYELLOW);
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
        ConsoleUI::setColor(WHITE);

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
            printRepeatMessage(109, 1, "DELETE", YELLOW);
        }
        else{
            printRepeatMessage(109, 1, "SELECT", YELLOW);
        }

        char key = _getch();

        if (27 == key && 8 == maxPerPage) {
            break;
        }
        else if (13 == key && 8 != maxPerPage){
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

// Displays the details of a specific order
// Shows order ID, list of purchased items, quantities, prices and total
void AdminUI::displayPurchasedHistory(vector<Order> orders) {
    if (orders.empty()) {
        printFrame(30, 14, 60, 3, LRED); 
        printMessage("NO PURCHASE HISTORY FOUND FOR THIS CUSTOMER.", 35, 15, LRED);
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
        ConsoleUI::setColor(LYELLOW);
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

        ConsoleUI::setColor(AQUA);
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
        ConsoleUI::setColor(LYELLOW);
        cout << "ORDER TOTAL: $" << orders[OrderIdx].getTotal();
        ConsoleUI::setColor(WHITE);

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

        ConsoleUI::setColor(LYELLOW);
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

// Displays sales statistics for items sold in the store
// Shows name, quantity sold, and revenue for each item, plus total revenue
void AdminUI::displaySaleStatistics(vector<SalesRecord> salesRecords, float totalRevenue) {
    if (salesRecords.empty()) {
        printFrame(30, 14, 60, 3, LRED); 
        printMessage("NO ITEM WAS SOLD!", 50, 15, LRED);
        sleepScreen(1200);
        return;
    }
    int x = 7;
    int y = 7;
    int maxPerPage = 8;
    int width = 106;
    int totalItems = salesRecords.size();
    int totalPages = (totalItems + maxPerPage - 1) / maxPerPage;
    int currentPage = 0;

    vector<int> cols = {4, 47, 70, 82, 94};

    while (true) {
        int startIdx = currentPage * maxPerPage;
        int endIdx = (startIdx + maxPerPage > totalItems ? totalItems : startIdx + maxPerPage);
        int rows = endIdx - startIdx + 1; 

        clearScreen(1, 7, 118, 22); 

        printFrameOptions(x, y, width, rows);

        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + 1);
            std::cout << char(179); 
            ConsoleUI::gotoXY(x + col, y);
            std::cout << char(194); 
            ConsoleUI::gotoXY(x + col, y + 2);
            std::cout << char(197); 
        }

        ConsoleUI::setColor(AQUA);
        ConsoleUI::gotoXY(x + 1, y + 1); 
        cout << "ID";
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); 
        cout << "SONG NAME";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); 
        cout << "ARTIST";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); 
        cout << "GENRE";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); 
        cout << "SOLD";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); 
        cout << "REVENUE";
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
            cout << salesRecords[i].getName();
            ConsoleUI::gotoXY(x + cols[1] + 1, curY); 
            cout << salesRecords[i].getArtist();
            ConsoleUI::gotoXY(x + cols[2] + 1, curY); 
            cout << salesRecords[i].getGenre();
            ConsoleUI::gotoXY(x + cols[3] + 1, curY); 
            cout << salesRecords[i].getSold();
            ConsoleUI::gotoXY(x + cols[4] + 1, curY); 
            cout << salesRecords[i].getRevenue();
        }

        // Bottom border
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, y + rows * 2 - 1);
            cout << char(179); 
            ConsoleUI::gotoXY(x + col, y + rows * 2);
            cout << char(193); 
        }

        ConsoleUI::setColor(LYELLOW);
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

        printFrame(40, 26, 40, 3, AQUA);
        ConsoleUI::gotoXY(50, 27);
        ConsoleUI::setColor(LYELLOW);
        cout << "TOTAL REVENUE: $" << totalRevenue;
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

// Collects information from the admin to create a new music item
// Returns a Music object with the user-provided details
Music AdminUI::getNewMusicDetails() {
    printFrameOptions(30, 10, 60, 5);
    ConsoleUI::setColor(AQUA);
    ConsoleUI::gotoXY(32, 11);
    cout << "ENTER MUSIC NAME  : ";
    ConsoleUI::gotoXY(32, 13);
    cout << "ENTER ARTIST      : ";
    ConsoleUI::gotoXY(32, 15);
    cout << "ENTER GENRE       : ";
    ConsoleUI::gotoXY(32, 17);
    cout << "ENTER PRICE       : ";
    ConsoleUI::gotoXY(32, 19);
    cout << "ENTER QUANTITY    : ";
    ConsoleUI::setColor(WHITE);

    // Variables to store new music item details

    // Get item name with validation
    string name = getValidatedInput<string>("ENTER MUSIC NAME: ",
        [](const string& prompt) {
            return InputChecker::checkString(prompt, 32, 11);
        },
        32, 11
    );

    // Get artist name with validation
    string artist = getValidatedInput<string>("ENTER ARTIST    : ",
        [](const string& prompt) {
            return InputChecker::checkString(prompt, 32, 13);
        },
        32, 13
    );

    // Get genre with validation
    string genre = getValidatedInput<string>("ENTER GENRE     : ",
        [](const string& prompt) {
            return InputChecker::checkString(prompt, 32, 15);
        },
        32, 15
    );

    // Get price with validation (must be non-negative)
    float price = getValidatedInput<float>(
        "ENTER PRICE     : ",
        [](const string& p) { 
            return InputChecker::checkFloat(p, 32, 17, 0.0F); 
        },
        32, 17
    );

    // Get quantity with validation (must be non-negative)
    int quantity = getValidatedInput<int>(
        "ENTER QUANTITY  : ",
        [](const string& p) { 
            return InputChecker::checkInt(p, 32, 19, 0); 
        },
        32, 19
    );

    // Create and return a new Music object with the collected data
    return Music(name, artist, genre, price, quantity);
}