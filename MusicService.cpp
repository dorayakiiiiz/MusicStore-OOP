/**
 * @file MusicService.cpp
 * @brief Implementation file for the MusicService class
 * 
 * @details Contains implementations for music inventory management functions
 *          including adding, removing, searching, and updating items
 */

#include "MusicService.h"
#include "IDataProvider.h"
#include "SQLDao.h"
#include <stdexcept>

#include <algorithm>

// Constructor
MusicService::MusicService() {
    dataProvider = make_shared<SqlDao>();
}

// Get the singleton instance of MusicService
shared_ptr<MusicService> MusicService::getInstance() {
    if (instance == nullptr) {
        instance = shared_ptr<MusicService>(new MusicService());
    }
    return instance;
}

// Get all music items from the repository
vector<Music> MusicService::getAllMusic() {
    // Get all music items from the repository
    return dataProvider->music()->getAll();
}


// Search music catalog by criteria and keyword
vector<Music> MusicService::searchMusic(const vector<Music>& items, SearchType criteria, const string& keyword) {
    SearchFactory factory;
    shared_ptr<ISearch> searchStrategy = factory.createSearch(criteria);
    
    if (!searchStrategy) {
        throw std::invalid_argument("Invalid search criteria: " + std::to_string(static_cast<int>(criteria)));
    }
    
    vector<Music> results = searchStrategy->search(items, keyword);
    return results;
}

// Add a new music item to the inventory
bool MusicService::addMusicItem(const Music& item) {
    return dataProvider->music()->add(item);
}

// Remove a music item from the inventory by ID
bool MusicService::removeMusicItem(int id) {
    return dataProvider->music()->deleteById(id);
}

// Update the price of a music item by ID
bool MusicService::updateMusicItemPrice(int id, float price) {
    // Validate ID
    if (id <= 0 || id > getAllMusic().size()) {
        return false;
    }
    // Update the item's price
    Music item = dataProvider->music()->getById(id);
    item.updatePrice(price);
    return dataProvider->music()->updateById(id, item);
}

// Remove sold-out items from the inventory
void MusicService::removeSoldOutItems() {
    // Get all music items from the repository
    vector<Music> items = dataProvider->music()->getAll();

    for (int i = 0; i < items.size(); ++i) {
        if (items[i].getQuantity() == 0) {
            items.erase(items.begin() + i);
            dataProvider->music()->deleteById(i + 1);
            --i;
        }
    }
}
