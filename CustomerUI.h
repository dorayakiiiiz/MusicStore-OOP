#ifndef _CUSTOMER_UI_H_
#define _CUSTOMER_UI_H_

#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "Order.h"


using std::cout, std::cin, std::string, std::vector;


class CustomerUI {
public:
    static void displayMenu();
    static void displayPurchasedHistory(const vector<Order>& orders, const string& username);
    static void displayMusicList(vector<Music>&);
};

#endif