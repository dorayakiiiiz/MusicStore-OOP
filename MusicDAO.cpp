#include "MusicDAO.h"
#include <fstream>
#include <sstream>
using std::ifstream, std::ofstream, std::stringstream, std::string, std::vector, std::cout, std::endl;

void MusicDAO::loadItems(vector<Music>& items) {
    ifstream file("music_info.txt");

    if (!file.is_open()) {
        throw ("Cannot open file!\n");
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

void MusicDAO::saveItems(const vector<Music>& items) {
    ofstream file("music_info.txt");
    if (!file.is_open()) {
        throw "Error opening music_info.txt!";
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