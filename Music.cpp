#include "Music.h"
#include <sstream>

Music::Music() {
    name = ""; artist = ""; genre = ""; price = 0; quantity = 0;
}

Music::Music(const string& name, const string& artist, const string& genre, const float& price, const int& quantity) {
    this->name = name;
    this->artist = artist; 
    this->genre = genre;
    this->price = price; 
    this->quantity = quantity;
}

string Music::getName() const {
    return name;
}

string Music::getArtist() const {
    return artist;
}

string Music::getGenre() const {
    return genre;
}

float Music::getPrice() const {
    return price;
}

int Music::getQuantity() const {
    return quantity;
}

string Music::toString() const {
    std::stringstream ss;
    ss << name << " - " << artist << " - " << genre << " - " << price << " - " << quantity;
    return ss.str();
}

void Music::updatePrice(const float& price) {
    this->price = price;
}

void Music::updateQuantity(const int& quantity) {
    this->quantity = quantity;
}

bool Music::operator==(const Music& other) const {
    return name == other.name && artist == other.artist;
}

