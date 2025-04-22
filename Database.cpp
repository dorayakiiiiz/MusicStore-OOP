#include "Database.h"

#include <fstream>
#include <sstream>
using std::ifstream, std::ofstream, std::stringstream;
Database* Database::getInstance() {
    if (!instance) {
        instance = new Database();
    }
    return instance;
}

Database::Database() {}

void Database::loadItems(vector<Music>& items) {
    ifstream file("music_info.txt");

    if (!file.is_open()) {
        throw ("Cannot open file!\n");
        return;
    }
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        string name, artist, genre, price, quantity;
        getline(ss, name, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');

        items.emplace_back(name, artist, genre, stof(price), stoi(quantity));
    }

    file.close();
}

void Database::saveItems(const vector<Music>& items) {
    ofstream file("music_info.txt");
    if (!file.is_open()) {
        throw "Error opening music_info.txt!";
        return;
    }

    file << "Name,Artist,Genre,Price,Quantity\n";
    for (const auto &item : items) {
        file << item.getName() << ","
             << item.getArtist() << ","
             << item.getGenre() << ","
             << item.getPrice() << ","
             << item.getQuantity() << "\n";
    }

    file.close();
}

void Database::loadCustomers(vector<shared_ptr<Customer>>& users) {
    ifstream file("customer_info.txt");
    if (!file.is_open()) {
        throw "Error opening customer_info.txt!";
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;

        getline(ss, username, ',');
        getline(ss, password, ',');

        users.push_back(make_shared<Customer>(username, password));

    }
    file.close();
}


void Database::saveCustomers(const vector<shared_ptr<Customer>>& users) {
    ofstream file("customer_info.txt");
    if (!file.is_open()) {
        throw "Error opening customer_info.txt!";
        return;
    }

    file << "Username,Password\n";
    for (int i = 0; i < users.size(); ++i) {
        file << users[i]->getUsername() << "," << users[i]->getPassword() << "\n";
    }

    file.close();
}

void Database::saveOrder(const Order& order) {
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

void Database::loadOrder(vector<Order>& orders) {
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

void Database::loadVoucher(vector<string>& vouchers) {
    ifstream file("vouchers.txt");
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        vouchers.push_back(line);
    }
    file.close();
}

void Database::saveVoucher(const vector<string>& vouchers) {
    ofstream file("vouchers.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Error opening vouchers.txt");
    }

    for (const auto& voucher : vouchers) {
        file << voucher << "\n";
    }
    file.close();
}