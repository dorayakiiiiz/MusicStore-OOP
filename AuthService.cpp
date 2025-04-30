#include "AuthService.h"
#include "utils.h"

// git commit commit

bool Authentication::registerUser(vector<shared_ptr<IUser>>& users, const string& username, const string& password, const string& role) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return false;
        }
    }
    if (role == "Customer") {
        users.push_back(make_shared<Customer>(username, password));
    } else {
        users.push_back(make_shared<Admin>(username, password));
    }
    return true;
}



shared_ptr<IUser> Authentication::loginUser(const vector<shared_ptr<IUser>>& users, const string& username, const string& password) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            return users[i];
        }
    }
    return nullptr;
}
