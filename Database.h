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
public:
    static void loadItems(vector<Music>&);
    static void saveItems(const vector<Music>&);
    static void loadCustomers(vector<shared_ptr<Customer>>&);
    static void saveCustomers(const vector<shared_ptr<Customer>>&);
    static void saveOrder(const Order&);
    static void loadOrder(vector<Order>&);
    static void loadVoucher(vector<string>&);
    static void saveVoucher(const vector<string>&);
};

#endif