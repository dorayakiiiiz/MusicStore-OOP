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

using std::cout, std::cin, std::vector, std::string;

// Displays a welcome message for the admin with their username
void AdminUI::displayWelcomeMessage(const string& username) {
    printMessage("welcome " + username + " to the admin menu!");
}

// Displays a formatted list of all music items in inventory
// Shows ID, name, artist, genre, price and quantity for each item
void AdminUI::displayMusicList(vector<Music>& items, int maxPerPage) {
    int x = 7;
    int y = 7.5;
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
        clearScreen(x, y, 106, maxPerPage * 2 + 4); // xóa vùng tối đa
        // Xóa page 
        clearScreen(2, 28, 10, 1); 

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
        ConsoleUI::gotoXY(x + cols[0] + 1, y + 1); std::cout << "Song name";
        ConsoleUI::gotoXY(x + cols[1] + 1, y + 1); std::cout << "Artist";
        ConsoleUI::gotoXY(x + cols[2] + 1, y + 1); std::cout << "Genre";
        ConsoleUI::gotoXY(x + cols[3] + 1, y + 1); std::cout << "Price";
        ConsoleUI::gotoXY(x + cols[4] + 1, y + 1); std::cout << "Quantity";

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
        ConsoleUI::gotoXY(2, 28);
        std::cout << "Page " << currentPage + 1 << "/" << totalPages;

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
        char key = _getch();
        if (27 == key || 17 == key) {
            break;
        }
        else if ((key == 'a' || key == 'A') && currentPage > 0) {
            --currentPage;
        } else if ((key == 'd' || key == 'D') && currentPage < totalPages - 1) {
            ++currentPage;
        }

    }
}

// Displays a formatted list of all registered users
// Shows ID, username, and role for each user
void AdminUI::displayUserList(const vector<shared_ptr<User>>& users) {
    int x = 20;
    int y = 7;
    int width = 80;
    int rows = users.size() + 1;

    printFrameOptions(x, y, width, rows);

    vector<int> cols = {5, 50};

    for (int col : cols) {
        ConsoleUI::gotoXY(x + col, y + 1);
        std::cout << char(179); // │
        ConsoleUI::gotoXY(x + col, y);
        std::cout << char(194); 
        ConsoleUI::gotoXY(x + col, y + 2);
        std::cout << char(197); 
    }
        //In header
    ConsoleUI::gotoXY(x + 1, y + 1);
    std::cout << "ID";
    ConsoleUI::gotoXY(x + cols[0] + 1, y + 1);
    std::cout << "Username";
    ConsoleUI::gotoXY(x + cols[1] + 1, y + 1);
    std::cout << "Role";

    for (int i = 1; i < rows; ++i) {
        int curY = y + i * 2 + 1;
        // Kẻ cột dọc
        for (int col : cols) {
            ConsoleUI::gotoXY(x + col, curY);
            std::cout << char(179); // │
            ConsoleUI::gotoXY(x + col, curY + 1);
            std::cout << char(197); 
        }

        //In
        ConsoleUI::gotoXY(x + 1, curY);
        std::cout << i;
        ConsoleUI::gotoXY(x + cols[0] + 1, curY);
        std::cout << users[i - 1]->getUsername();
        ConsoleUI::gotoXY(x + cols[1] + 1, curY);
        std::cout << (Role::ADMIN == users[i - 1]->getRole() ? "Admin" : "Customer");
    }

    for (int col : cols) {
        ConsoleUI::gotoXY(x + col, y + rows*2 - 1);
        std::cout << char(179); // │
        ConsoleUI::gotoXY(x + col, y + rows*2);
        std::cout << char(193); 
    }
    ConsoleUI::gotoXY(x + 1, y + rows*2 - 1);
    std::cout << rows - 1;
    ConsoleUI::gotoXY(x + cols[0] + 1, y + rows*2 - 1);
    std::cout << users[rows - 2]->getUsername();
    ConsoleUI::gotoXY(x + cols[1] + 1, y + rows*2 - 1);
    std::cout << (Role::ADMIN == users[rows - 2]->getRole() ? "Admin" : "Customer");
}

// Displays the details of a specific order
// Shows order ID, list of purchased items, quantities, prices and total
void AdminUI::displayPurchasedHistory(const Order& order, int id) {
    cout << "\tOrder " << id << ": \n";
    cout << "\tPurchased items:\n";

    const vector<Music>& purchasedItems = order.getPurchasedItems();

    // Display details for each item in the order
    for (const auto& item : purchasedItems) {
        cout << "\t- " << item.getName() << " - Quantity: " << item.getQuantity()
             << "\t- Price per unit: $" << item.getPrice()
             << "\t- Total: $" << item.getPrice() * item.getQuantity() << '\n';
    }
    cout << "\tOrder total: $" << order.getTotal() << '\n';
}

// Displays sales statistics for items sold in the store
// Shows name, quantity sold, and revenue for each item, plus total revenue
void AdminUI::displaySaleStatistics(vector<SalesRecord> salesRecords, float totalRevenue) {
    // Iterate through each sales record
    for (const auto& record : salesRecords) {
        cout << "\tItem: " << record.getName() << " - Sold: "
             << record.getSold() << " - Revenue: $" << record.getRevenue() << "\n";
    }
    cout << "\tTotal revenue: $" << totalRevenue << "\n";
}

// Collects information from the admin to create a new music item
// Returns a Music object with the user-provided details
Music AdminUI::getNewMusicDetails() {

    // Variables to store new music item details

    // Get item name with validation
    string name = getValidatedInput<string>("Enter music name: ",
        [](const string& prompt) {
            return InputChecker::validateString(prompt);
        }
    );

    // Get artist name with validation
    string artist = getValidatedInput<string>("Enter artist: ",
        [](const string& prompt) {
            return InputChecker::validateString(prompt);
        }
    );

    // Get genre with validation
    string genre = getValidatedInput<string>("Enter genre: ",
        [](const string& prompt) {
            return InputChecker::validateString(prompt);
        }
    );

    // Get price with validation (must be non-negative)
    float price = getValidatedInput<float>(
        "\tEnter price: ",
        [](const std::string& p) { return InputChecker::validateFloat(p, 0.0F); } 
    );

    // Get quantity with validation (must be non-negative)
    int quantity = getValidatedInput<int>(
        "\tEnter quantity: ",
        [](const std::string& p) { return InputChecker::validateInt(p, 0); } // Dùng lambda để truyền thêm tham số min
    );

    // Create and return a new Music object with the collected data
    return Music(name, artist, genre, price, quantity);
}
