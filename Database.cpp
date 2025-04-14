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

void Database::loadItems(vector<MusicItem>& items) {
    ifstream file("music_info.txt");

    if (!file.is_open()) {
        throw ("Cannot open file!\n");
        return;
    }
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, artist, genre, price, quantity;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');

        items.emplace_back(stoi(id), name, artist, genre, stof(price), stoi(quantity));
    }

    file.close();
}

void Database::saveItems(const vector<MusicItem>& items) {
    ofstream file("music_info.txt");
    if (!file.is_open()) {
        throw "Error opening music_info.txt!";
        return;
    }

    file << "ID,Name,Artist,Genre,Price,Quantity\n";
    for (const auto &item : items) {
        file << item.getID() << ","
             << item.getName() << ","
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
    file << order.getOrderId() << ","
         << order.getUsername() << ","
         << order.getTotal() << ",";
    const auto& items = order.getPurchasedItems();
    for (int i = 0; i < items.size(); ++i) {
        file << items[i].first << ":" << items[i].second;
        if (i != items.size() - 1) {
            file << ";";
        }
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
        string orderId, username, totalStr, itemsStr;
        getline(ss, orderId, ',');
        getline(ss, username, ',');
        getline(ss, totalStr, ',');
        getline(ss, itemsStr);

        vector<pair<int, int>> purchasedItems;
        stringstream itemsStream(itemsStr);
        string itemPair;
        while (getline(itemsStream, itemPair, ';')) {
            int colonPos = itemPair.find(':');
            int id = stoi(itemPair.substr(0, colonPos));
            int quantity = stoi(itemPair.substr(colonPos + 1));
            purchasedItems.emplace_back(id, quantity);
        }
        Order order(orderId, username, purchasedItems, stof(totalStr));
        orders.push_back(order);
    }
}