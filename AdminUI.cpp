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
        cout << "Product: " << name << " - Sold: "
        << stats.first << " - Revenue: $" << stats.second << "\n";
        totalRevenue += stats.second;
    }
    cout << "Total revenue: $" << totalRevenue << "\n";
}

Music AdminUI::getNewMusicDetails() {
    string name = getInput("Enter name: ");
    string artist = getInput("Enter artist: ");
    string genre = getInput("Enter genre: ");
    float price = stof(getInput("Enter price: "));
    int quantity = stoi(getInput("Enter quantity: "));
    
    return Music(name, artist, genre, price, quantity);
}
