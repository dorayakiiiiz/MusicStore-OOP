#include "CustomerUI.h"
#include "utils.h"

void CustomerUI::displayWelcomeMessage(const string& username) {
    printMessage("welcome " + username + " to the music store!");
}

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
        printDashLine();
    }
}

void CustomerUI::displayMusicList(vector<Music>& items) {
    cout << "ID - Name - Artist - Genre - Price - Quantity\n";
    for (int i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].toString() << '\n';
    }
}



void CustomerUI::displayCart(const vector<Music>& items) {
    for (int i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << " - " << items[i].getName() << " - Quantity: " << items[i].getQuantity()
             << " - Price per unit: $" << items[i].getPrice()
             << " - Total: $" << items[i].getPrice() * items[i].getQuantity() << '\n';
    }
}

void CustomerUI::displayNoResultsMessage() {
    printMessage("No results found!");
}


void CustomerUI::displaySearchResults(vector<Music>& results) {
    printMessage("Search results: ");
    displayMusicList(results);
}


void CustomerUI::displayEmptyCartMessage() {
    printMessage("Cart is empty! Please add items to cart before checking out.");
}

void CustomerUI::displayOrderDetails(const string& username, const vector<Music>& items, float total) {
    printMessage("Your order details: ");
    printMessage("Username: " + username);
    printMessage("Purchased items: ");
    displayCart(items);
    printMessage("Total: $" + std::to_string(total));
    printDashLine();
}

void CustomerUI::displayVoucherList(const vector<shared_ptr<IDiscount>>& vouchers) {
    printMessage("You have the following vouchers available: ");
    for (int i = 0; i < vouchers.size(); ++i) {
        cout << i + 1 << ". " << vouchers[i]->toString() << '\n';
    }
}


void CustomerUI::displayDiscountOptions() {
    printMessage("Congratulations! As the total is over $50, you will receive a discount voucher for your next purchase");
    printMessage("What type of discount would you like to apply?");
    printMessage("1. Percentage discount");
    printMessage("2. Fixed amount discount");
}


void CustomerUI::displayOrderSuccessMessage() {
    printMessage("Order placed successfully! Thank you for your purchase!");
}

void CustomerUI::displayLogoutMessage() {
    printMessage("You have logged out successfully!");
}

void CustomerUI::displayCartWarningMessage() {
    printMessage("You have items in your cart! Please check out before logging out.");
}

void CustomerUI::displayInvalidChoiceMessage() {
    printMessage("Invalid choice! Please try again.");
}