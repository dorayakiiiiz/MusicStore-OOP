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

// Delete a user account by username
bool UserService::deleteUser(const string& username) {
    // Get all users from the repository
    vector<shared_ptr<User>> users = getAllUsers();
    int index = findUserByUsername(users, username);
    if (index != -1) {
        return Registry::getSingleton<IUserRepository>()->deleteById(index + 1);
    }
    return false;
}

// Find a user by username, returns the index or -1 if not found
int UserService::findUserByUsername(const vector<shared_ptr<User>>& users, const string& username) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return i;
        }
    }
    return -1;
}
