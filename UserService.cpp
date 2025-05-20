#include "UserService.h"
#include "Registry.h"
#include "IUserRepository.h"

// Get all user accounts from the repository
vector<shared_ptr<User>> UserService::getAllUsers() {
    // Get all users from the repository
    vector<shared_ptr<User>> users = Registry::getSingleton<IUserRepository>()->getAll();
    return users;
}

// get a user account by ID
shared_ptr<User> UserService::getUserById(int id) {
    return Registry::getSingleton<IUserRepository>()->getById(id);
}

// Delete a user account by id
bool UserService::deleteUserById(int id) {
    return Registry::getSingleton<IUserRepository>()->deleteById(id);
}

// Get all customer accounts from the repository
vector<shared_ptr<User>> UserService::getAllCustomers() {
    // Get all users from the repository
    vector<shared_ptr<User>> users = Registry::getSingleton<IUserRepository>()->getAll();
    vector<shared_ptr<User>> customers;
    for (const auto& user : users) {
        if (user->getRole() == Role::CUSTOMER) {
            customers.push_back(user);
        }
    }
    return customers;
}
