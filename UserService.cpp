#include "UserService.h"
#include "IDataProvider.h"
#include "SQLDao.h"

// Get the singleton instance of UserService
shared_ptr<UserService> UserService::getInstance() {
    if (instance == nullptr) {
        instance = make_shared<UserService>();
    }
    return instance;
}

// Get all user accounts from the repository
vector<shared_ptr<User>> UserService::getAllUsers() {
    auto dataProvider = make_shared<SqlDao>();
    return dataProvider->user()->getAll();
}

// get a user account by ID
shared_ptr<User> UserService::getUserById(int id) {
    auto dataProvider = make_shared<SqlDao>();
    return dataProvider->user()->getById(id);
}

// Delete a user account by id
bool UserService::deleteUserById(int id) {
    auto dataProvider = make_shared<SqlDao>();
    return dataProvider->user()->deleteById(id);
}

// Get all customer accounts from the repository
vector<shared_ptr<User>> UserService::getAllCustomers() {
    auto dataProvider = make_shared<SqlDao>();
    vector<shared_ptr<User>> users = dataProvider->user()->getAll();
    // Filter customers from the list of users
    vector<shared_ptr<User>> customers;
    for (const auto& user : users) {
        if (user->getRole() == Role::CUSTOMER) {
            customers.push_back(user);
        }
    }
    return customers;
}
