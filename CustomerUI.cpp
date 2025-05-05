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
    printMessage("welcome " + username + " to the music store!");
}

// Displays the main customer menu options
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

// Displays the order history for a specific customer
// Shows all previous orders with details of purchased items and totals
void CustomerUI::displayPurchasedHistory(const vector<Order>& orders, const string& username) {
    if (orders.empty()) {
        printMessage("No purchase history found!");
        return;
    }
    // Iterate through all orders for this customer
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

// Displays a formatted list of all available music items
void CustomerUI::displayMusicList(vector<Music>& items) {
    cout << "ID - Name - Artist - Genre - Price - Quantity\n";
    for (int i = 0; i < items.size(); ++i) {
        cout << i + 1 << " - " << items[i].toString() << '\n';
    }
}

// Displays the current items in the shopping cart
// Shows name, quantity, unit price and total price for each item
void CustomerUI::displayCart(const vector<Music>& items) {
    for (int i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << " - " << items[i].getName() << " - Quantity: " << items[i].getQuantity()
             << " - Price per unit: $" << items[i].getPrice()
             << " - Total: $" << items[i].getPrice() * items[i].getQuantity() << '\n';
    }
}

// Displays a message when no search results are found
void CustomerUI::displayNoResultsMessage() {
    printMessage("No results found!");
}

// Displays search results from a music search operation
void CustomerUI::displaySearchResults(vector<Music>& results) {
    printMessage("Search results: ");
    displayMusicList(results);
}

// Displays a message when attempting to checkout with an empty cart
void CustomerUI::displayEmptyCartMessage() {
    printMessage("Cart is empty! Please add items to cart before checking out.");
}

// Displays order details before confirming checkout
// Shows username, list of items, and total price
void CustomerUI::displayOrderDetails(const string& username, const vector<Music>& items, float total) {
    printMessage("Your order details: ");
    printMessage("Username: " + username);
    printMessage("Purchased items: ");
    displayCart(items);
    printMessage("Total: $" + std::to_string(total));
    printDashLine();
}

// Displays the list of available discount vouchers for the customer
void CustomerUI::displayVoucherList(const vector<shared_ptr<Discount>>& vouchers) {
    printMessage("You have the following vouchers available: ");
    for (int i = 0; i < vouchers.size(); ++i) {
        cout << i + 1 << ". " << vouchers[i]->toString() << '\n';
    }
}

// Displays discount options after a large purchase (over $50)
// Shows available discount types the customer can choose
void CustomerUI::displayDiscountOptions() {
    printMessage("Congratulations! As the total is over $50, you will receive a discount voucher for your next purchase");
    printMessage("What type of discount would you like to apply?");
    printMessage("1. Percentage discount");
    printMessage("2. Fixed amount discount");
}

// Displays a success message after completing an order
void CustomerUI::displayOrderSuccessMessage() {
    printMessage("Order placed successfully! Thank you for your purchase!");
}

// Displays a message when the customer logs out
void CustomerUI::displayLogoutMessage() {
    printMessage("You have logged out successfully!");
}

// Displays a warning when attempting to log out with items still in cart
void CustomerUI::displayCartWarningMessage() {
    printMessage("You have items in your cart! Please check out before logging out.");
}

// Displays a message for invalid menu choices
void CustomerUI::displayInvalidChoiceMessage() {
    printMessage("Invalid choice! Please try again.");
}