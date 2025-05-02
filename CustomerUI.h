#ifndef _CUSTOMER_UI_H_
#define _CUSTOMER_UI_H_

#include <iostream>
#include <string>
#include <vector>
#include "Order.h"
#include "Music.h"
#include "Discount.h"
#include <tuple>
#include "utils.h"

using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple;

class CustomerUI {
public:
    static void displayWelcomeMessage(const string& username);
    static void displayMenu();

    static void displayPurchasedHistory(const vector<Order>& orders, const string& username);
    static void displayMusicList(vector<Music>& items);


    static void displayCart(const vector<Music>& items);
    static void displayNoResultsMessage();


    static void displaySearchResults(vector<Music>& results);


    static void displayEmptyCartMessage();
    static void displayOrderDetails(const string& username, const vector<Music>& items, float total);
    static void displayVoucherList(const vector<shared_ptr<IDiscount>>& vouchers);

    
    static void displayDiscountOptions();

    static void displayOrderSuccessMessage();
    static void displayLogoutMessage();
    static void displayCartWarningMessage();
    static void displayInvalidChoiceMessage();
};

#endif