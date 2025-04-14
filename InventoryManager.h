#ifndef _INVENTORY_MANAGER_H_
#define _INVENTORY_MANAGER_H_

#include "MusicItem.h"
#include "Database.h"
#include <vector>
using std::vector;

class InventoryManager {
private:
    vector<MusicItem>& items;
public:
    InventoryManager(vector<MusicItem>&);
    void addItem(const MusicItem&);
    void removeItem(int);
    void updateItemPrice(int, float);
    const vector<MusicItem>& getAllItems() const;
    vector<MusicItem> searchItems(const string& keyword);
};


#endif