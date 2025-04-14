#include "InventoryManager.h"

InventoryManager::InventoryManager(vector<MusicItem>& items) : items(items) {}

void InventoryManager::addItem(const MusicItem& item) {
    items.push_back(item);
    Database::getInstance()->saveItems(items);
}

vector<MusicItem> InventoryManager::searchItems(const string& keyword) {
    vector<MusicItem> results;
    for (int i = 0; i < items.size(); ++i) {
        if (items[i].getName().find(keyword) != string::npos) {
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

vector<MusicItem>& InventoryManager::getAllItems() const {
    return items;
}