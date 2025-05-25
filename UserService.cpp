#include "UserService.h"
#include "IDataProvider.h"
#include "SQLDao.h"

// Constructor
UserService::UserService(shared_ptr<IDataProvider> provider) {
    this->dataProvider = provider;
}

// Get the singleton instance of UserService
shared_ptr<UserService> UserService::getInstance(shared_ptr<IDataProvider> provider) {
    if (instance == nullptr) {
        // If no provider is passed, use the default SqlDao
        if (!provider) {
            provider = make_shared<SqlDao>();
        }
        instance = shared_ptr<UserService>(new UserService(provider));
    }
    return instance;
}

// Get all user accounts from the repository
vector<shared_ptr<User>> UserService::getAllUsers() {
    return dataProvider->user()->getAll();
}

// get a user account by ID
shared_ptr<User> UserService::getUserById(int id) {
    return dataProvider->user()->getById(id);
}

// Delete a user account by id
bool UserService::deleteUserById(int id) {
    return dataProvider->user()->deleteById(id);
}

// Get all customer accounts from the repository
vector<shared_ptr<User>> UserService::getAllCustomers() {
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
