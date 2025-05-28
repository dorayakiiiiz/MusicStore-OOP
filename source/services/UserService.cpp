#include "UserService.h"
#include "../database/IDataProvider.h"
#include "../database/SQLDao.h"

// Constructor
UserService::UserService(shared_ptr<IDataProvider> provider) {
    this->_dataProvider = provider;
}

// Get the singleton instance of UserService
shared_ptr<UserService> UserService::getInstance(shared_ptr<IDataProvider> provider) {
    if (_instance == nullptr) {
        // If no provider is passed, use the default SqlDao
        if (!provider) {
            provider = make_shared<SqlDao>();
        }
        _instance = shared_ptr<UserService>(new UserService(provider));
    }
    return _instance;
}

// Get all user accounts from the repository
vector<shared_ptr<User>> UserService::getAllUsers() {
    return _dataProvider->user()->getAll();
}

// get a user account by ID
shared_ptr<User> UserService::getUserById(int id) {
    return _dataProvider->user()->getById(id);
}

// Delete a user account by id
bool UserService::deleteUserById(int id) {
    return _dataProvider->user()->deleteById(id);
}

// Get all customer accounts from the repository
vector<shared_ptr<User>> UserService::getAllCustomers() {
    vector<shared_ptr<User>> users = _dataProvider->user()->getAll();
    // Filter customers from the list of users
    vector<shared_ptr<User>> customers;
    for (const auto& user : users) {
        if (user->getRole() == Role::CUSTOMER) {
            customers.push_back(user);
        }
    }
    return customers;
}
