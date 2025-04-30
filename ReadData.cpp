#include "ReadData.h"

using std::string;

vector<Music> ReadMusic::readData(const string& filename) const {
    ifstream file(filename);
    vector<Music> items;
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }
    string line;
    getline(file, line); // skip header line
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
    return items;
}

vector<shared_ptr<IUser>> ReadUser::readData(const string& filename) const {
    ifstream file(filename);
    vector<shared_ptr<IUser>> users;
    if (!file.is_open()) {
        throw "Error opening file!";
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string username, password, role;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, role);
        if (role.empty()) {
            users.push_back(make_shared<Customer>(username, password));
        } else {
            users.push_back(make_shared<Admin>(username, password));
        }

    }
    file.close();
    return users;
}

vector<Order> ReadOrder::readData(const string& filename) const {
    ifstream file(filename);
    vector<Order> orders;
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
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

    file.close();
    return orders;
}


vector<shared_ptr<IDiscount>> ReadDiscount::readData(const string& filename) const {
    ifstream file(filename);
    vector<shared_ptr<IDiscount>> vouchers;
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }
    string line;
    while (getline(file, line)) {
        shared_ptr<IDiscount> voucher = IDiscount::toDiscount(line);
        vouchers.push_back(voucher);
    }
    file.close();
    return vouchers;
}