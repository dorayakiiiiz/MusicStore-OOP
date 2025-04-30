#include "CustomerUI.h"

void CustomerUI::displayMenu() {
    printHeader("CUSTOMER MENU");
    vector<string> options = {
        "See your purchased history",
        "See music list",
        "Find item",
        "Add to cart",
        "Remove items from cart",
        "Check out",
        "Log out\n",
    };
    printMenu(options);
}

void CustomerUI::displayPurchasedHistory(const vector<Order>& orders, const string& username) {
    if (orders.empty()) {
        printMessage("No purchase history found!");
        return;
    }
    for (int i = 0; i < orders.size(); ++i) {
        cout << "Order " << i + 1 << ": \n";
        vector<Music> items = orders[i].getPurchasedItems();
        for (const auto& item : items) {
            cout << " - " << item.getName() << " - Quantity: " << item.getQuantity()
            << " - Price per unit: $" << item.getPrice()
            << " - Total: $" << item.getPrice() * item.getQuantity() << '\n';
        }
        cout << "Order total: $" << orders[i].getTotal() << '\n';
    }
}

void CustomerUI::displayMusicList(vector<Music>& items) {
    cout << "ID - Name - Artist - Genre - Price - Quantity\n";
    for (int i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". ";
        items[i].displayItems();
    }
}