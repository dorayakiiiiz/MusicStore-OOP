#include "AdminUI.h"
#include "utils.h"
#include "InputValidator.h"

using std::cout, std::cin, std::vector, std::string;

// Displays a welcome message for the admin with their username
void AdminUI::displayWelcomeMessage(const string& username) {
    printMessage("welcome " + username + " to the admin menu!");
    printDashLine();
}

// Displays the main admin menu options
void AdminUI::displayMenu() {
    printHeader("ADMIN MENU");

    vector<string> options = {
        "See music list",          
        "Add new items",          
        "Remove items",            
        "Update price items",      
        "View users list",        
        "View all customers purchased history",  
        "Delete customers",        
        "View sale statistics",    
        "Log out\n"                
    };
    
    printMenu(options);
}

// Displays a formatted list of all music items in inventory
// Shows ID, name, artist, genre, price and quantity for each item
void AdminUI::displayMusicList(vector<Music>& items) {
    cout << "ID - Name - Artist - Genre - Price - Quantity\n";
    for (int i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].toString() << '\n';
    }
}

// Displays a formatted list of all registered users
// Shows ID, username, password, and role for each user
void AdminUI::displayUserList(const vector<shared_ptr<IUser>>& users) {
    cout << "ID - Username - Password - Role\n";
    for (int i = 0; i < users.size(); ++i) {
        cout << i + 1 << ". " << users[i]->toString() << '\n';
    }
}

// Displays the details of a specific order
// Shows order ID, list of purchased items, quantities, prices and total
void AdminUI::displayPurchasedHistory(const Order& order, int id) {
    cout << "Order " << id << ": \n";
    cout << "Purchased items:\n";

    const vector<Music>& purchasedItems = order.getPurchasedItems();

    // Display details for each item in the order
    for (const auto& item : purchasedItems) {
        cout << "- " << item.getName() << " - Quantity: " << item.getQuantity()
             << " - Price per unit: $" << item.getPrice()
             << " - Total: $" << item.getPrice() * item.getQuantity() << '\n';
    }
    cout << "Order total: $" << order.getTotal() << '\n';
}

// Displays sales statistics for items sold in the store
// Shows name, quantity sold, and revenue for each item, plus total revenue
void AdminUI::displaySaleStatistics(vector<pair<string, pair<int, float>>>& itemStats) {
    float totalRevenue = 0;
    // Iterate through each item's statistics
    for (const auto& [name, stats] : itemStats) {
        cout << "Item: " << name << " - Sold: "
        << stats.first << " - Revenue: $" << stats.second << "\n";
        totalRevenue += stats.second;
    }
    cout << "Total revenue: $" << totalRevenue << "\n";
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
        std::tie(isValid, name, error) = InputValidator::validateString("Enter name: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get artist name with validation
    do {
        std::tie(isValid, artist, error) = InputValidator::validateString("Enter artist: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get genre with validation
    do {
        std::tie(isValid, genre, error) = InputValidator::validateString("Enter genre: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get price with validation (must be non-negative)
    do {
        std::tie(isValid, price, error) = InputValidator::validateFloat("Enter price: ", 0.0F);
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    // Get quantity with validation (must be non-negative)
    do {
        std::tie(isValid, quantity, error) = InputValidator::validateInt("Enter quantity: ", 0);
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);
    
    // Create and return a new Music object with the collected data
    return Music(name, artist, genre, price, quantity);
}
