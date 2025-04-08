#include "SystemManager.h"

SystemManager::SystemManager() {
    loadData();
}

SystemManager* SystemManager::getInstance() {
    if (!instance) {
        instance = new SystemManager();
    }
    return instance;
}

void SystemManager::loadData() {
    DatabaseManager* db = DatabaseManager::getInstance();
    db->loadItems(items);

    vector<Customer*> cus;
    db->loadCustomers(cus);
    for (int i = 0; i < cus.size(); ++i) {
        customers.push_back(shared_ptr<Customer>(cus[i]));
    }
}

void SystemManager::saveData() {
    DatabaseManager* db = DatabaseManager::getInstance();
    db->saveItems(items);

    vector<Customer*> cus;
    for (int i = 0; i < customers.size(); ++i) {
        cus.push_back(customers[i].get());
    }
    db->saveCustomers(cus);
}

void SystemManager::registerCustomer() {
    string username;
    string password;
    cout << "Input your username: ";
    cin >> username;
    cout << "Input your password: ";
    cin >> password;
    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i]->getUsername() == username) {
            cout << "Username is already existed. Please try again!\n";
            return;
        }
    }
    shared_ptr<Customer> newCustomer = make_shared<Customer>(username, password);
    customers.push_back(newCustomer);
    cout << "Register successfully!\n";
}

shared_ptr<Customer> SystemManager::loginCustomer() {
    string username;
    string password;
    cout << "Input username: ";
    cin >> username;
    cout << "Input password: ";
    cin >> password;

    for (int i = 0; i < customers.size(); ++i) {
        cout << customers[i]->getUsername() << " - " << customers[i]->getPassword() << "\n";
    }

    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i]->getUsername() == username && customers[i]->getPassword() == password) {
            cout << "Login successfully!\n";
            return customers[i];
        }
    }
    cout << "Username or password is incorrect.\n";
    return nullptr;
}

bool SystemManager::loginAdmin() {
    string passkey;
    cout << "Input Admin Passkey: ";
    cin >> passkey;

    Admin admin;
    if (AdminPasskey::getInstance()->isValid(passkey)) {
        cout << "Login successfully!\n";
        return true;
    } else {
        cout << "Invalid passkey!\n"; 
        return false;
    }
}

void SystemManager::run() {
    while (1) {
        cout << "---------- WELCOME TO MUSIC STORE ----------\n";
        cout << "1. Sign up\n";
        cout << "2. Login\n"; 
        cout << "3. Exit\n";

        int choice;
        cin >> choice;

        if (choice == 1) {
            registerCustomer();
        } else if (choice == 2) {
            cout << "You are: 1. Admin - 2. Customer\n";
            
            int accountType;
            cin >> accountType;
            
            if (accountType == 1) {
                if (loginAdmin()) {
                    cout << "---------- MANAGEMENT STORE FOR ADMINISTRATOR ----------\n";

                    // insert code hereee

                    system("pause");
                
                }
            } else if (accountType == 2) {
                shared_ptr<Customer> customer = loginCustomer();
                if (customer) {
                    cout << "---------- MUSIC STORE - LET US RESCUE YOUR EAR ----------\n";


                    // insert code hereeee


                    system("pause");
                }
            } else {
                cout << "Invalid option. Please try again!\n";
            }
        } else if (choice == 3) {
            saveData();
            cout << "---------- GOODBYE AND NEVER SEE YOU AGAIN ---------\n";
            break;
        }
    }
}
