#include "Authentication.h"
#include "InventoryManager.h"
#include "MusicDAO.h"
#include "CustomerDAO.h"
#include "Music.h"
#include "User.h"
#include "Cart.h"
#include "Discount.h"
#include "utils.h"
#include "AdminController.h"
#include "CustomerController.h"


#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <windows.h>

using std::cin, std::cout, std::vector, std::string, std::exception;

int main() {

    // commit commit
    
    vector<Music> items;
    vector<shared_ptr<Customer>> customers;

    MusicDAO::loadItems(items);
    CustomerDAO::loadCustomers(customers);


    InventoryManager inventory(items);
    Authentication auth;
    Cart currentCart;
    shared_ptr<Customer> currentCustomer = nullptr;

    while (1) {
        system("cls");
        displayMenu({
            "---------- WELCOME TO MUSIC STORE ----------",
            "1. Sign up",
            "2. Login",
            "3. Exit\n"
        });

        int choice = stoi(getInput("Input choice: "));

        switch (choice) {
            case 1: {
                string username = getInput("Input username: ");
                string password = getInput("Input password: ");
                bool success = auth.registerCustomer(customers, username, password);
                if (success) {
                    cout << "Sign up successfully!\n";
                    customers.push_back(make_shared<Customer>(username, password));
                    CustomerDAO::saveCustomers(customers);
                } else {
                    cout << "Username already exists. Please try again!\n";
                }
                break;
            }
            case 2: {
                displayMenu({"\nYou are: 1. Admin - 2. Customer"});
                int role = stoi(getInput("\nInput role: "));

                if (role == 1) {
                    string passkey = getInput("Input admin passkey: ");

                    if (auth.loginAdmin(passkey)) {
                        cout << "Login successfully\n";
                        AdminController::run(inventory);

                    } else {

                        cout << "Invalid passkey. Please try again!\n";

                    }
                } else if (role == 2) {
                    string username = getInput("Input username: ");
                    string password = getInput("Input password: ");

                    currentCustomer = auth.loginCustomer(customers, username, password);
                    if (currentCustomer) {
                        cout << "Login successfully!\n";

                        CustomerController::run(inventory, currentCart, *currentCustomer);

                    } else {
                        cout << "\nUsername or password is incorrect.\n";
                    }
                }
            }
            break;
            case 3:
                MusicDAO::saveItems(items);
                CustomerDAO::saveCustomers(customers);
                cout << "---------- GOODBYE! ----------\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again!\n";
        }
        Sleep(2500);
    }
    
    return 0;
}
