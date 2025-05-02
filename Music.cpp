#include "Music.h"
#include <sstream>

// Default constructor - initializes an empty music item
Music::Music() {
    name = ""; artist = ""; genre = ""; price = 0; quantity = 0;
}

// Parameterized constructor - initializes a music item with the given details
Music::Music(const string& name, const string& artist, const string& genre, const float& price, const int& quantity) {
    this->name = name;
    this->artist = artist; 
    this->genre = genre;
    this->price = price; 
    this->quantity = quantity;
}

// Get the name of the music
string Music::getName() const {
    return name;
}

// Get the artist of the music
string Music::getArtist() const {
    return artist;
}

// Get the genre of the music
string Music::getGenre() const {
    return genre;
}

// Get the price of the music
float Music::getPrice() const {
    return price;
}

// Get the quantity available in inventory
int Music::getQuantity() const {
    return quantity;
}

// Convert the music object to a string representation for display
string Music::toString() const {
    std::stringstream ss;
    ss << name << " - " << artist << " - " << genre << " - " << price << " - " << quantity;
    return ss.str();
}

// Update the price of the music item
void Music::updatePrice(const float& price) {
    this->price = price;
}

// Update the quantity of the music item in inventory
void Music::updateQuantity(const int& quantity) {
    this->quantity = quantity;
}

// Compare two music items by name and artist
bool Music::operator==(const Music& other) const {
    return name == other.name && artist == other.artist;
}

