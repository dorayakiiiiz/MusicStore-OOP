#include "ReadData.h"

using std::string;


// Reads music data from a file and returns a vector of Music objects
vector<Music> ReadMusic::readData(const string& filename) const {
    ifstream file(filename);
    vector<Music> items;

    // Check if the file can be opened
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    string line;
    getline(file, line); // Skip the header line

    // Read each line and parse the music data
    while (getline(file, line)) {
        stringstream ss(line);
        string name, artist, genre, price, quantity;

        // Extract fields separated by commas
        getline(ss, name, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');

        // Create a Music object and add it to the vector
        items.emplace_back(name, artist, genre, stof(price), stoi(quantity));
    }

    file.close();
    return items;
}

// Reads user data from a file and returns a vector of IUser objects
vector<shared_ptr<IUser>> ReadUser::readData(const string& filename) const {
    ifstream file(filename);
    vector<shared_ptr<IUser>> users;

    // Check if the file can be opened
    if (!file.is_open()) {
        throw "Error opening file!";
    }

    string line;
    getline(file, line); // Skip the header line

    // Read each line and parse the user data
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password, role;

        // Extract fields separated by commas
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, role);

        // Create a User object based on the role and add it to the vector
        if (role.empty()) {
            users.push_back(make_shared<Customer>(username, password));
        } else {
            users.push_back(make_shared<Admin>(username, password));
        }
    }

    file.close();
    return users;
}

// Reads order data from a file and returns a vector of Order objects
vector<Order> ReadOrder::readData(const string& filename) const {
    ifstream file(filename);
    vector<Order> orders;

    // Check if the file can be opened
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    string line;

    // Read each line and parse the order data
    while (getline(file, line)) {
        stringstream ss(line);
        string username, totalPrice, items;

        // Extract fields separated by '|'
        getline(ss, username, '|');
        getline(ss, totalPrice, '|');
        getline(ss, items);

        vector<Music> purchasedItems;
        stringstream itemsStream(items);
        string itemSS;

        // Parse each purchased item
        while (getline(itemsStream, itemSS, '|')) {
            stringstream itemStream(itemSS);
            string name, artist, genre, price, quantity;

            // Extract fields separated by ';'
            getline(itemStream, name, ';');
            getline(itemStream, artist, ';');
            getline(itemStream, genre, ';');
            getline(itemStream, price, ';');
            getline(itemStream, quantity, '|');

            // Create a Music object and add it to the purchased items
            Music item(name, artist, genre, stof(price), stoi(quantity));
            purchasedItems.emplace_back(item);
        }

        // Create an Order object and add it to the vector
        Order order(username, purchasedItems, stof(totalPrice));
        orders.push_back(order);
    }

    file.close();
    return orders;
}

// Reads discount data from a file and returns a vector of IDiscount objects
vector<shared_ptr<Discount>> ReadDiscount::readData(const string& filename) const {
    ifstream file(filename);
    vector<shared_ptr<Discount>> vouchers;

    // Check if the file can be opened
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    string line;

    // Read each line and parse the discount data
    while (getline(file, line)) {
        shared_ptr<Discount> voucher = Discount::fromString(line);
        vouchers.push_back(voucher);
    }

    file.close();
    return vouchers;
}