#include "AdminUI.h"

using std::cout, std::cin, std::vector, std::string;

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
    int idx = 1;
    for (int i = 0; i < items.size(); ++i) {
        if (items[i].getQuantity() == 0) {
            continue;
        }  
        cout << idx++ << ". ";
        items[i].displayItems();
    }
}

void AdminUI::displayUserList(vector<shared_ptr<IUser>>& users) {
    cout << "ID - Username - Password - Role\n";
    for (int i = 0; i < users.size(); ++i) {
        cout << i + 1 << ". ";
        users[i]->displayInfo();
    }
}

void AdminUI::displayPurchasedHistory(const Order& order, int id) {
    cout << "Order " << id << ": \n";
    cout << "Purchased items:\n";

    vector<Music> purchasedItems = order.getPurchasedItems();

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
        cout << "Product: " << name << " - Sold : "
        << stats.first << " - Revenue: $" << stats.second << "\n";
        totalRevenue += stats.second;
    }
    cout << "Total revenue: $" << totalRevenue << "\n";
}