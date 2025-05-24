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
#include "IDataProvider.h"
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
private:
    inline static shared_ptr<MusicService> instance = nullptr; /**< Singleton instance of MusicService */

    shared_ptr<IDataProvider> dataProvider; /**< Data provider for accessing music data */

    MusicService(); /**< Private constructor for singleton pattern */
public:

    /**
     * @brief Get the singleton instance of MusicService
     * 
     * @return shared_ptr<MusicService> Pointer to the singleton instance
     */
    static shared_ptr<MusicService> getInstance();

    /**
     * @brief Get all music items in the inventory
     * 
     * @return vector<Music> Vector of all music items
     */
    vector<Music> getAllMusic();

    /**
     * @brief Add a new music item to the inventory
     * 
     * @param items Reference to the vector of music items
     * @param item The new music item to add
     * @return bool True if successful, false if item already exists
     */
    bool addMusicItem(const Music& item);
    
    /**
     * @brief Remove a music item from the inventory by ID
     * 
     * @param items Reference to the vector of music items
     * @param id Index of the item to remove
     * @return bool True if successful, false if invalid ID
     */
    bool removeMusicItem(int id);

    /**
     * @brief Update the price of a music item by ID
     * 
     * @param items Reference to the vector of music items
     * @param id Index of the item to update
     * @param price New price for the item
     * @return bool True if successful, false if invalid ID
     */
    bool updateMusicItemPrice(int id, float price);

    /**
     * @brief Search music catalog by criteria (name/artist/genre) and keyword
     * 
     * @param items Vector of music items to search through
     * @param criteria Search criteria (name, artist, or genre)
     * @param keyword Keyword to search for
     * @return vector<Music> Vector of music items matching the search criteria
     * @throws std::invalid_argument If an invalid search criteria is provided
     */
    vector<Music> searchMusic(const vector<Music>& items, SearchType criteria, const string& keyword);

    /**
     * @brief Remove sold-out items from the inventory
     * 
     * @param items Reference to the vector of music items
     */
    void removeSoldOutItems();
};

#endif