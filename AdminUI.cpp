#include "AdminUI.h"
#include "utils.h"

using std::cout, std::cin, std::vector, std::string;

void AdminUI::displayWelcomeMessage(const string& username) {
    printMessage("welcome " + username + " to the admin menu!");
    printDashLine();
}

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

void AdminUI::displayMusicList(vector<Music>& items) {
    cout << "ID - Name - Artist - Genre - Price - Quantity\n";
    for (int i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].toString() << '\n';
    }
}

void AdminUI::displayUserList(const vector<shared_ptr<IUser>>& users) {
    cout << "ID - Username - Password - Role\n";
    for (int i = 0; i < users.size(); ++i) {
        cout << i + 1 << ". " << users[i]->toString() << '\n';
    }
}

void AdminUI::displayPurchasedHistory(const Order& order, int id) {
    cout << "Order " << id << ": \n";
    cout << "Purchased items:\n";

    const vector<Music>& purchasedItems = order.getPurchasedItems();

    for (const auto& item : purchasedItems) {
        cout << "- " << item.getName() << " - Quantity: " << item.getQuantity()
             << " - Price per unit: $" << item.getPrice()
             << " - Total: $" << item.getPrice() * item.getQuantity() << '\n';
    }
    cout << "Order total: $" << order.getTotal() << '\n';
}

void AdminUI::displaySaleStatistics(vector<pair<string, pair<int, float>>>& itemStats) {
    float totalRevenue = 0;
    for (const auto& [name, stats] : itemStats) {
        cout << "Item: " << name << " - Sold: "
        << stats.first << " - Revenue: $" << stats.second << "\n";
        totalRevenue += stats.second;
    }
    cout << "Total revenue: $" << totalRevenue << "\n";
}

Music AdminUI::getNewMusicDetails() {
    bool isValid;
    Error error;

    string name, artist, genre;
    float price = 0.0f;
    int quantity = 0;


    do {
        std::tie(isValid, name, error) = getStringInput("Enter name: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    do {
        std::tie(isValid, artist, error) = getStringInput("Enter artist: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    do {
        std::tie(isValid, genre, error) = getStringInput("Enter genre: ");
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    do {
        std::tie(isValid, price, error) = getFloatInput("Enter price: ", 0.0F);
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);

    do {
        std::tie(isValid, quantity, error) = getIntInput("Enter quantity: ", 0);
        if (!isValid) {
            printMessage(error.message);
            pauseScreen();
            continue;
        }
    } while (!isValid);
    
    return Music(name, artist, genre, price, quantity);
}
