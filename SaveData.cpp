#include "SaveData.h"


void SaveMusic::saveData(const string& filename, const vector<Music>& items) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    file << "Name,Artist,Genre,Price,Quantity\n";
    for (const auto& item : items) {
        file << item.getName() << ","
             << item.getArtist() << ","
             << item.getGenre() << ","
             << item.getPrice() << ","
             << item.getQuantity() << "\n";
    }

    file.close();
}


void SaveUser::saveData(const string& filename, const vector<shared_ptr<IUser>>& users) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    file << "Username,Password\n";
    for (const auto& user : users) {
        file << user->getUsername() << "," << user->getPassword() << ",";
        if (user->getRole() == "Admin") {
            file << "A\n";
        } else {
            file << '\n';
        }
    }

    file.close();
}


void SaveOrder::saveData(const string& filename, const vector<Order>& orders) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }

    for (const auto& order : orders) {
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
    }

    file.close();
}

void SaveDiscount::saveData(const string& filename, const vector<shared_ptr<IDiscount>>& vouchers) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file!");
    }
    for (const auto& voucher : vouchers) {
        file << voucher->toString() << "\n";
    }
    file.close();
}