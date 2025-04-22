#include "OrderDAO.h"
#include <fstream>
#include <sstream>
using std::ifstream, std::ofstream, std::stringstream, std::string, std::vector, std::cout, std::endl;

void OrderDAO::saveOrder(const Order& order) {
    ofstream file("orders.txt", std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening orders.txt");
    }

    //format: username|total|name;arist;genre;price;totalquantity|
    
    file << order.getUsername() << "|"
         << order.getTotal() << "|";
    const auto& items = order.getPurchasedItems();
    for (int i = 0; i < items.size(); ++i) {
        file << items[i].getName() << ";"
             << items[i].getArtist() << ";"
             << items[i].getGenre() << ";"
             << items[i].getPrice() << ";"
             << items[i].getQuantity() << "|";
    }
    file << "\n";
    file.close();
}

void OrderDAO::loadOrder(vector<Order>& orders) {
    ifstream file("orders.txt");
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, totalPrice, items;
        getline(ss, username, '|');
        getline(ss, totalPrice, '|');
        getline(ss, items);

        vector<Music> purchasedItems;
        stringstream itemsStream(items);
        string itemSS;
        while (getline(itemsStream, itemSS, '|')) {
            stringstream itemsStream(itemSS);
            string name, artist, genre, price, quantity;
            getline(itemsStream, name, ';');
            getline(itemsStream, artist, ';');
            getline(itemsStream, genre, ';');
            getline(itemsStream, price, ';');
            getline(itemsStream, quantity, '|');

            Music item(name, artist, genre, stof(price), stoi(quantity));
            purchasedItems.emplace_back(item);
        }
        Order order(username, purchasedItems, stof(totalPrice));
        orders.push_back(order);
    }
}