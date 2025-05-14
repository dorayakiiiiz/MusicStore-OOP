#include "UserService.h"

// Delete a user account by username
bool UserService::deleteUser(vector<shared_ptr<User>>& users, const string& username) {
    int index = findUserByUsername(users, username);
    if (index != -1) {
        users.erase(users.begin() + index);
        return true;
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
