/**
 * @file MusicService.cpp
 * @brief Implementation file for the MusicService class
 * 
 * @details Contains implementations for music inventory management functions
 *          including adding, removing, searching, and updating items
 */

#include "MusicService.h"
#include <stdexcept>

#include <algorithm>


// Search music catalog by criteria and keyword
vector<Music> MusicService::searchMusic(const vector<Music>& items, SearchType criteria, const string& keyword) {
    shared_ptr<ISearch> searchStrategy = SearchFactory::createSearch(criteria);
    
    if (!searchStrategy) {
        throw std::invalid_argument("Invalid search criteria: " + std::to_string(static_cast<int>(criteria)));
    }
    
    vector<Music> results = searchStrategy->search(items, keyword);
    return results;
}

// Add a new music item to the inventory
bool MusicService::addMusicItem(vector<Music>& items, const Music& item) {
    // Check if item already exists
    for (const auto& i : items) {
        if (i == item) {
            return false; 
        }
    }
    // Add the new item
    items.push_back(item);
    return true;
}

// Remove a music item from the inventory by ID
bool MusicService::removeMusicItem(vector<Music>& items, int id) {
    // Validate ID
    if (id < 0 || id >= items.size()) {
        return false;
    }
    // Remove the item
    items.erase(items.begin() + id);
    return true;
}

// Update the price of a music item by ID
bool MusicService::updateMusicItemPrice(vector<Music>& items, int id, float price) {
    // Validate ID
    if (id < 0 || id >= items.size()) {
        return false;
    }
    // Update the price
    items[id].updatePrice(price);
    return true;
}

// Remove sold-out items from the inventory
void MusicService::removeSoldOutItems(vector<Music>& items) {
    items.erase(remove_if(items.begin(), items.end(), [](const Music& item) {
        return item.getQuantity() == 0;
    }), items.end());
}
