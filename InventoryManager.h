#ifndef _INVENTORY_MANAGER_H_
#define _INVENTORY_MANAGER_H_

#include "Music.h"
#include "Database.h"
#include <vector>
using std::vector;

class InventoryManager {
private:
    vector<Music>& items;
public:
    InventoryManager(vector<Music>&);
    void addItem(const Music&);
    bool removeItem(int);
    void updateItemPrice(int, float);
    vector<Music>& getAllItems() const;
    vector<Music> searchItems(const string& keyword);
};


#endif