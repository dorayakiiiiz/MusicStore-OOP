#ifndef _SALES_RECORD_H_
#define _SALES_RECORD_H_

#include <string>
using std::string;

/**
 * @brief Represents a sales record for a music item
 * 
 * @details Contains information about the music item, artist, genre, quantity sold, and revenue generated
 */
class SalesRecord {
private:
    string name;    /**> The name of the music item */
    string artist; /**> The artist of the music item */
    string genre; /**> The genre of the music item */
    int sold;   /**> The quantity sold */
    float revenue; /**> The revenue generated from the music item */
public:
    /**
     * @brief Default constructor
     */
    SalesRecord();

    /**
     * @brief Parameterized constructor
     * 
     * @param name The name of the music item
     * @param artist The artist of the music item
     * @param genre The genre of the music item
     * @param sold The quantity sold
     * @param revenue The revenue generated from the music item
     */
    SalesRecord(const string& name, const string& artist, const string& genre, int sold, float revenue);

    /**
     * @brief Get the name of the music item
     * 
     * @return string The name of the music item
     */
    string getName() const;

    /**
     * @brief Get the artist of the music item
     * 
     * @return string The artist of the music item
     */
    string getArtist() const;

    /**
     * @brief Get the genre of the music item
     * 
     * @return string The genre of the music item
     */
    string getGenre() const;

    /**
     * @brief Get the quantity sold of the music item
     * 
     * @return int The quantity sold
     */
    int getSold() const;
    /**
     * @brief Get the revenue generated from the music item
     * 
     * @return float The revenue generated
     */
    float getRevenue() const;
};


#endif