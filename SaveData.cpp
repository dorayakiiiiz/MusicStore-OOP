#include "SaveData.h"

// Saves music data to a file
void SaveMusic::saveData(const string& filename, const vector<Music>& items) const {
    ofstream file(filename);

    // Check if the file can be opened
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    // Write the header line
    file << "Name,Artist,Genre,Price,Quantity\n";

    // Write each music item to the file
    for (const auto& item : items) {
        file << item.getName() << ","
             << item.getArtist() << ","
             << item.getGenre() << ","
             << item.getPrice() << ","
             << item.getQuantity() << "\n";
    }

    file.close();
}

// Saves user data to a file
void SaveUser::saveData(const string& filename, const vector<shared_ptr<IUser>>& users) const {
    ofstream file(filename);

    // Check if the file can be opened
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    // Write the header line
    file << "Username,Password\n";

    // Write each user to the file
    for (const auto& user : users) {
        file << user->getUsername() << "," << user->getPassword() << ",";
        if (user->getRole() == "Admin") {
            file << "A\n"; // Mark admin users with 'A'
        } else {
            file << '\n'; // Leave role empty for customers
        }
    }

    file.close();
}

// Saves order data to a file
void SaveOrder::saveData(const string& filename, const vector<Order>& orders) const {
    ofstream file(filename);

    // Check if the file can be opened
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    // Write each order to the file
    for (const auto& order : orders) {
        file << order.getUsername() << "|"
             << order.getTotal() << "|";

        const auto& items = order.getPurchasedItems();

        // Write each purchased item in the order
        for (int i = 0; i < items.size(); ++i) {
            file << items[i].getName() << ";"
                 << items[i].getArtist() << ";"
                 << items[i].getGenre() << ";"
                 << items[i].getPrice() << ";"
                 << items[i].getQuantity() << "|";
        }

        file << "\n";
    }

    file.close();
}

// Saves discount data to a file
void SaveDiscount::saveData(const string& filename, const vector<shared_ptr<IDiscount>>& vouchers) const {
    ofstream file(filename);

    // Check if the file can be opened
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    // Write each discount voucher to the file
    for (const auto& voucher : vouchers) {
        file << voucher->toString() << "\n";
    }

    file.close();
}