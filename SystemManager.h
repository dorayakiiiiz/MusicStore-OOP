#ifndef _SYSTEM_MANAGER_H_
#define _SYSTEM_MANAGER_H_

#include <memory>
#include <iostream>
#include "User.h"
#include "DatabaseManager.h"

using std::vector, std::shared_ptr, std::make_shared;
using std::cin, std::cout;

class SystemManager {
private:
    vector<shared_ptr<Customer>> customers;
    vector<MusicItem> items;
    inline static SystemManager* instance = nullptr;
    SystemManager();

    void loadData();
    void saveData();

public:
    static SystemManager* getInstance();

    void registerCustomer();
    shared_ptr<Customer> loginCustomer();
    bool loginAdmin();
    void run();
};

#endif