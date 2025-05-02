#ifndef _MUSIC_ITEM_H_
#define _MUSIC_ITEM_H_

#include <string>

using std::string;

// Class representing a music item that can be purchased in the store
class Music {
private:
    string name;     // Name of the music track
    string artist;   // Artist who performed the music
    string genre;    // Genre of the music (e.g., Pop, Rock, etc.)
    float price;     // Price of the music item
    int quantity;    // Available quantity in inventory

public:
    // Default constructor - creates an empty music item
    Music();
    
    // Parameterized constructor - creates a music item with specified details
    Music(const string&, const string&, const string&, const float&, const int&);
    
    // Default destructor
    ~Music() = default;

    // Getters
    string getName() const;      // Get the name of the music
    string getArtist() const;    // Get the artist name
    string getGenre() const;     // Get the genre
    float getPrice() const;      // Get the price
    int getQuantity() const;     // Get the available quantity
    
    // Converts the music object to a string representation
    string toString() const; 
    
    // Updates the price of the music item
    void updatePrice(const float&);
    
    // Updates the quantity of the music item
    void updateQuantity(const int&);

    // Overload equality operator to compare music items by name and artist
    bool operator==(const Music&) const;
};

#endif