#ifndef _DATABASE_
#define _DATABASE_

#include "Music.h"
#include "User.h"
#include "Order.h"
#include <vector>
#include <memory>
using std::cin, std::cout, std::vector, std::shared_ptr, std::make_shared;

// class Database quản lí các thao tác đọc/ghi file cho toàn bộ chương trình
class Database {
private:
    inline static Database* instance = nullptr;
    Database();
public:
    static Database* getInstance();
    void loadItems(vector<Music>&);
    void saveItems(const vector<Music>&);
    void loadCustomers(vector<shared_ptr<Customer>>&);
    void saveCustomers(const vector<shared_ptr<Customer>>&);
    void saveOrder(const Order&);
    void loadOrder(vector<Order>&);
    void loadVoucher(vector<string>&);
    void saveVoucher(const vector<string>&);
};

#endif