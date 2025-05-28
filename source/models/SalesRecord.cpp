#include "SalesRecord.h"
#include <string>

// Default constructor
SalesRecord::SalesRecord() : _name(""), _artist(""), _genre(""), _sold(0), _revenue(0.0f) {}

// Parameterized constructor
SalesRecord::SalesRecord(const string& name, const string& artist, const string& genre, int sold, float revenue)
    : _name(name), _artist(artist), _genre(genre), _sold(sold), _revenue(revenue) {}

// Get the name of the music item
string SalesRecord::getName() const {
    return _name;
}

// Get the artist of the music item
string SalesRecord::getArtist() const {
    return _artist;
}

// Get the genre of the music item
string SalesRecord::getGenre() const {
    return _genre;
}

// Get the quantity sold of the music item
int SalesRecord::getSold() const {
    return _sold;
}

// Get the revenue generated from the music item
float SalesRecord::getRevenue() const {
    return _revenue;
}