#include "SalesRecord.h"

// Default constructor
SalesRecord::SalesRecord() {}

// Parameterized constructor
SalesRecord::SalesRecord(const string& name, const string& artist, const string& genre, int sold, float revenue)
    : name(name), artist(artist), genre(genre), sold(sold), revenue(revenue) {}

// Get the name of the music item
string SalesRecord::getName() const {
    return name;
}

// Get the artist of the music item
string SalesRecord::getArtist() const {
    return artist;
}

// Get the genre of the music item
string SalesRecord::getGenre() const {
    return genre;
}

// Get the quantity sold of the music item
int SalesRecord::getSold() const {
    return sold;
}

// Get the revenue generated from the music item
float SalesRecord::getRevenue() const {
    return revenue;
}