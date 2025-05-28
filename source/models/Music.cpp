/**
 * @file Music.cpp
 * @brief Implementation file for the Music class
 * 
 * @details Contains implementations for the Music class which represents
 *          a music item in the inventory system
 */

#include "Music.h"
#include <sstream>

// Default constructor - initializes an empty music item
Music::Music() {
    _name = ""; _artist = ""; _genre = ""; _price = 0; _quantity = 0;
}

// Parameterized constructor - initializes a music item with the given details
Music::Music(const string& name, const string& artist, const string& genre, const float& price, const int& quantity) {
    this->_name = name;
    this->_artist = artist; 
    this->_genre = genre;
    this->_price = price; 
    this->_quantity = quantity;
}

// Get the name of the music
string Music::getName() const {
    return _name;
}

// Get the artist of the music
string Music::getArtist() const {
    return _artist;
}

// Get the genre of the music
string Music::getGenre() const {
    return _genre;
}

// Get the price of the music
float Music::getPrice() const {
    return _price;
}

// Get the quantity available in inventory
int Music::getQuantity() const {
    return _quantity;
}

// Update the price of the music item
void Music::updatePrice(const float& price) {
    this->_price = price;
}

// Update the quantity of the music item in inventory
void Music::updateQuantity(const int& quantity) {
    this->_quantity = quantity;
}

// Compare two music items by name and artist
bool Music::operator==(const Music& other) const {
    return _name == other._name && _artist == other._artist;
}