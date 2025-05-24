/**
 * @file AdminUI.cpp
 * @brief Implementation file for the AdminUI class
 * 
 * @details Contains implementations of all display functions and input collection
 *          methods for the administrator interface
 */

#include "AdminUI.h"
#include "utils.h"
#include "InputValidator.h"

using std::cout, std::cin, std::vector, std::string;

// Displays a welcome message for the admin with their username
void AdminUI::displayWelcomeMessage(const string& username) {
    printMessage("welcome " + username + " to the admin menu!");
}

// Displays a formatted list of all music items in inventory
// Shows ID, name, artist, genre, price and quantity for each item
void AdminUI::displayMusicList(vector<Music>& items) {
    printFrameMusicList(items);
}

// Displays a formatted list of all registered users
// Shows ID, username, and role for each user
void AdminUI::displayUserList(const vector<shared_ptr<User>>& users) {
    cout << "\tID - Username - Role\n";
    for (int i = 0; i < users.size(); ++i) {
        cout << '\t' << i + 1 << " - " << users[i]->toString() << '\n';
    }
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
    bool isValid;
    Error error;

    // Variables to store new music item details
    string name, artist, genre;
    float price = 0.0f;
    int quantity = 0;

    // Get item name with validation
    do {
        std::tie(isValid, name, error) = InputValidator::validateString("\tEnter name: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get artist name with validation
    do {
        std::tie(isValid, artist, error) = InputValidator::validateString("\tEnter artist: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get genre with validation
    do {
        std::tie(isValid, genre, error) = InputValidator::validateString("\tEnter genre: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get price with validation (must be non-negative)
    do {
        std::tie(isValid, price, error) = InputValidator::validateFloat("\tEnter price: ", 0.0F);
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get quantity with validation (must be non-negative)
    do {
        std::tie(isValid, quantity, error) = InputValidator::validateInt("\tEnter quantity: ", 0);
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);
    
    // Create and return a new Music object with the collected data
    return Music(name, artist, genre, price, quantity);
}
