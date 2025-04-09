#include "InventoryManager.h"

InventoryManager::InventoryManager(vector<MusicItem>& items) : items(items) {}

void InventoryManager::addItem(const MusicItem& item) {
    items.push_back(item);
    DatabaseManager::getInstance()->saveItems(items);
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

void InventoryManager::removeItem(int id) {
    items.erase(items.begin() + id);
}

const vector<MusicItem>& InventoryManager::getAllItems() const {
    return items;
}