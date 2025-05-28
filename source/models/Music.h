/**
 * @file Music.h
 * @brief Header file for the Music class
 * 
 * @details Defines the Music class which represents music items
 *          sold in the store, containing properties like name, artist, price, etc.
 */

#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <string>

using std::string;

/**
 * @brief Class representing a music item that can be purchased in the store
 */
class Music {
private:
    string _name;     /**< Name of the music track */
    string _artist;   /**< Artist who performed the music */
    string _genre;    /**< Genre of the music (e.g., Pop, Rock, etc.) */
    float _price;     /**< Price of the music item */
    int _quantity;    /**< Available quantity in inventory */

public:
    /**
     * @brief Default constructor - creates an empty music item
     */
    Music();
    
    /**
     * @brief Parameterized constructor - creates a music item with specified details
     * 
     * @param name Name of the music track
     * @param artist Artist who performed the music
     * @param genre Genre of the music
     * @param price Price of the music item
     * @param quantity Available quantity in inventory
     */
    Music(const string&, const string&, const string&, const float&, const int&);
    
    /**
     * @brief Default destructor
     */
    ~Music() = default;

    /**
     * @brief Get the name of the music
     * @return string The name of the music track
     */
    string getName() const;
    
    /**
     * @brief Get the artist of the music
     * @return string The artist name
     */
    string getArtist() const;
    
    /**
     * @brief Get the genre of the music
     * @return string The genre
     */
    string getGenre() const;
    
    /**
     * @brief Get the price of the music
     * @return float The price
     */
    float getPrice() const;
    
    /**
     * @brief Get the available quantity
     * @return int The available quantity
     */
    int getQuantity() const;
    
    /**
     * @brief Updates the price of the music item
     * @param price New price to set
     */
    void updatePrice(const float&);
    
    /**
     * @brief Updates the quantity of the music item
     * @param quantity New quantity to set
     */
    void updateQuantity(const int&);

    /**
     * @brief Overload equality operator to compare music items by name and artist
     * @param other The music item to compare with
     * @return bool True if the items have the same name and artist
     */
    bool operator==(const Music&) const;
};

#endif