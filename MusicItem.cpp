#include "MusicItem.h"

// fix this .cpp

#include <iostream>
using std::cin, std::cout;
MusicItem::MusicItem(const string& name, const string& artist, const string& genre, const float& price, const int& quantity) {
    this->name = name;
    this->artist = artist; this->genre = genre;
    this->price = price; this->quantity = quantity;
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
    cout << name << " - " << artist << " - ";
    cout << genre << " - " << price << " - " << quantity << "\n";

}
void MusicItem::updatePrice(const float& price) {
    this->price = price;
}
void MusicItem::updateQuantity(const int& quantity) {
    this->quantity = quantity;
}

bool MusicItem::operator==(const MusicItem& other) const {
    return name == other.name && artist == other.artist && genre == other.genre && price == other.price;
}

