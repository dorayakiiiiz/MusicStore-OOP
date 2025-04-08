#include "MusicItem.h"

#include <iostream>
using std::cin, std::cout;
MusicItem::MusicItem(const int& id, const string& name, const string& artist, const string& genre, const float& price, const int& quantity) {
    this->id = id; this->name = name;
    this->artist = artist; this->genre = genre;
    this->price = price; this->quantity = quantity;
}
    

int MusicItem::getID() const {
    return id;
}

string MusicItem::getName() const {
    return name;
}

string MusicItem::getArtist() const {
    return artist;
}

string MusicItem::getGenre() const {
    return genre;
}

float MusicItem::getPrice() const {
    return price;
}

int MusicItem::getQuantity() const {
    return quantity;
}

void MusicItem::displayItems() {
    cout << id << " - " << name << " - " << artist;
    cout << " - " << genre << " - " << price << " - " << quantity << "\n";

}
void MusicItem::updatePrice(const float& price) {
    this->price = price;
}
void MusicItem::updateQuantity(const int& quantity) {
    this->quantity = quantity;
}
