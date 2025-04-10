#ifndef _DATABASE_MANAGER_
#define _DATABASE_MANAGER_

#include "MusicItem.h"
#include "User.h"
#include "Order.h"
#include <vector>
#include <memory>
using std::cin, std::cout, std::vector, std::shared_ptr, std::make_shared;

// class DatabaseManager quản lí các thao tác đọc/ghi file cho toàn bộ chương trình
class DatabaseManager {
private:
    inline static DatabaseManager* instance = nullptr;
    DatabaseManager();
public:
    static DatabaseManager* getInstance();
    void loadItems(vector<MusicItem>&);
    void saveItems(const vector<MusicItem>&);
    void loadCustomers(vector<shared_ptr<Customer>>&);
    void saveCustomers(const vector<shared_ptr<Customer>>&);
    void saveOrder(const Order&);
};

#endif