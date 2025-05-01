#ifndef _ADMIN_UI_H_
#define _ADMIN_UI_H_

#include <iostream>
#include <vector>
#include <utility>
#include "Music.h"
#include "User.h"
#include "Order.h"
#include "Discount.h"
#include <memory>
using std::shared_ptr, std::pair;

class AdminUI {
public:
    static void displayWelcomeMessage(const string& username);
    static void displayMenu();
    static void displayMusicList(vector<Music>& items);
    static void displayUserList(const vector<shared_ptr<IUser>>& users);
    static void displayPurchasedHistory(const Order& order, int id);
    static void displaySaleStatistics(vector<pair<string, pair<int, float>>>& itemStats);
    static Music getNewMusicDetails();
};

#endif