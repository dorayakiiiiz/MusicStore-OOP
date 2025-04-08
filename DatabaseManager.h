#ifndef _DATABASE_MANAGER_
#define _DATABASE_MANAGER_

#include "MusicItem.h"
#include "User.h"
#include <vector>
using std::cin, std::cout, std::vector;

class DatabaseManager {
private:
    inline static DatabaseManager* instance = nullptr;
    DatabaseManager();
public:
    static DatabaseManager* getInstance();
    void loadItems(vector<MusicItem>&);
    void saveItems(const vector<MusicItem>&);
    void loadCustomers(vector<Customer*>&);
    void saveCustomers(const vector<Customer*>&);
};

#endif