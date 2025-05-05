/**
 * @file MusicService.h
 * @brief Header file for the MusicService class
 * 
 * @details Defines the MusicService class which provides functionality
 *          for managing music inventory, including adding, removing, and searching
 */

#ifndef _MUSIC_SERVICE_H_
#define _MUSIC_SERVICE_H_

#include "Music.h"
#include "Search.h"
#include "SearchFactory.h"
#include <vector>
#include <string>
#include <memory>

using std::vector, std::string, std::shared_ptr, std::make_shared;

/**
 * @brief Service class for managing music inventory
 * 
 * @details Provides methods for adding, removing, updating, and searching music items in the inventory
 */
class MusicService {
public:

    /**
     * @brief Default constructor
     */
    MusicService() = default;

    /**
     * @brief Default destructor
     */
    ~MusicService() = default;


    /**
     * @brief Add a new music item to the inventory
     * 
     * @param items Reference to the vector of music items
     * @param item The new music item to add
     * @return bool True if successful, false if item already exists
     */
    bool addMusicItem(vector<Music>& items, const Music& item);
    
    /**
     * @brief Remove a music item from the inventory by ID
     * 
     * @param items Reference to the vector of music items
     * @param id Index of the item to remove
     * @return bool True if successful, false if invalid ID
     */
    bool removeMusicItem(vector<Music>& items, int id);
    
    /**
     * @brief Update the price of a music item by ID
     * 
     * @param items Reference to the vector of music items
     * @param id Index of the item to update
     * @param price New price for the item
     * @return bool True if successful, false if invalid ID
     */
    bool updateMusicItemPrice(vector<Music>& items, int id, float price);

    /**
     * @brief Search music catalog by criteria (name/artist/genre) and keyword
     * 
     * @param items Vector of music items to search through
     * @param criteria Search criteria (name, artist, or genre)
     * @param keyword Keyword to search for
     * @return vector<Music> Vector of music items matching the search criteria
     * @throws std::invalid_argument If an invalid search criteria is provided
     */
    vector<Music> searchMusic(const vector<Music>& items, const string& criteria, const string& keyword);

    /**
     * @brief Remove sold-out items from the inventory
     * 
     * @param items Reference to the vector of music items
     */
    static void removeSoldOutItems(vector<Music>& items);
};

#endif