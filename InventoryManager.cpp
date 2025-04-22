#include "InventoryManager.h"
#include "MusicDAO.h"

InventoryManager::InventoryManager(vector<Music>& items) : items(items) {}

void InventoryManager::addItem(const Music& item) {
    items.push_back(item);
    MusicDAO::saveItems(items);
}

vector<Music> InventoryManager::searchItems(const string& keyword) {
    string lowerKeyword = keyword;
    for (auto& c : lowerKeyword) {
        c = tolower(c);
    }
    vector<Music> results;
    for (int i = 0; i < items.size(); ++i) {
        string lowerName = items[i].getName();
        for (auto& c : lowerName) {
            c = tolower(c);
        }
        if (lowerName.find(lowerKeyword) != string::npos) {
            results.push_back(items[i]);
        }
    }
    return results;
}

void InventoryManager::updateItemPrice(int id, float price) {
    items[id].updatePrice(price);
}

bool InventoryManager::removeItem(int id) {
    if (id < 0 || id >= items.size()) {
        return false;
    }
    items.erase(items.begin() + id);
    return true;
}

vector<Music>& InventoryManager::getAllItems() const {
    return items;
}