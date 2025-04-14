#include "Authentication.h"
#include "UI.h"

void Authentication::registerCustomer(vector<shared_ptr<Customer>>& customers) {
    string username = UI::getInput("Input your username: ");
    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i]->getUsername() == username) {
            cout << "Username is already existed. Please try again!\n";
            return;
        }
    }
    string password = UI::getInput("Input your password: ");
    customers.push_back(make_shared<Customer>(username, password));
    cout << "Register successfully!\n";
}

shared_ptr<Customer> Authentication::loginCustomer(const vector<shared_ptr<Customer>>& customers) {
    string username = UI::getInput("Input username: ");
    string password = UI::getInput("Input password: ");
    
    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i]->getUsername() == username && customers[i]->getPassword() == password) {
            cout << "\nLogin successfully!\n";
            return customers[i];
        }
    }
    cout << "\nUsername or password is incorrect.\n";
    return nullptr;
}

bool Authentication::loginAdmin() {
    string passkey = UI::getInput("Input admin passkey: ");

    if (AdminPasskey::getInstance()->isValid(passkey)) {
        cout << "\nLogin successfully!\n";
        return true;
    } else {
        cout << "\nInvalid passkey!\n"; 
        return false;
    }
}