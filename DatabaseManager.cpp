#include "DatabaseManager.h"

#include <fstream>
#include <sstream>
using std::ifstream, std::ofstream, std::stringstream;
DatabaseManager* DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return instance;
}

DatabaseManager::DatabaseManager() {}

void DatabaseManager::loadItems(vector<MusicItem>& items) {
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

void DatabaseManager::saveItems(const vector<MusicItem>& items) {
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

void DatabaseManager::loadCustomers(vector<shared_ptr<Customer>>& users) {
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


void DatabaseManager::saveCustomers(const vector<shared_ptr<Customer>>& users) {
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

void DatabaseManager::saveOrder(const Order& order) {
    ofstream file("orders.txt", std::ios::app);
    if (!file.is_open()) {
        file << order.getOrderId() << ","<<order.getTotal() << "\n";
        file.close();
    }
}