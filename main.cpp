#include "Database.h"
#include "Authentication.h"
#include "InventoryManager.h"
#include "MusicItem.h"
#include "User.h"
#include "Cart.h"
#include "Discount.h"
#include "UI.h"
#include "AdminController.h"
#include "CustomerController.h"


#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <windows.h>

using std::cin, std::cout, std::vector, std::string, std::exception;

int main() {
    
    Database* db = Database::getInstance();
    vector<MusicItem> items;
    vector<shared_ptr<Customer>> customers;

    try {
        
        db->loadItems(items);
        db->loadCustomers(customers);

    } catch (exception ex) {
        cout << "Error while loading data: " << ex.what() << "\n";
        return 1;
    }

    InventoryManager inventory(items);
    Authentication auth;
    Cart currentCart;
    shared_ptr<Customer> currentCustomer = nullptr;

    while (1) {
        UI::displayMenu({
            "---------- WELCOME TO MUSIC STORE ----------",
            "1. Sign up",
            "2. Login",
            "3. Exit"
        });

        int choice = stoi(UI::getInput("Input choice: "));

        switch (choice) {
            case 1:
                auth.registerCustomer(customers);
                db->saveCustomers(customers);
                break;
            case 2: {
                UI::displayMenu({"You are: 1. Admin - 2. Customer"});
                int role = stoi(UI::getInput("Input role: "));
                if (role == 1) {
                    if (auth.loginAdmin()) {
                        // cout << "Login to admin successfully\n";

                        AdminController::run(inventory);
                        // code hereee


                        system("pause");
                    } else {
                        // cout << "Invalid passkey. Please try again!\n";
                    }
                } else if (role == 2) {
                    currentCustomer = auth.loginCustomer(customers);
                    if (currentCustomer) {
                        //cout << "Login to customer UI successfully!\n";

                        // code heree
                        CustomerController::run(inventory, currentCart, *currentCustomer);

                        system("pause");
                    }
                }
            }
            break;
            case 3:
                db->saveItems(items);
                db->saveCustomers(customers);
                cout << "---------- GOODBYE! ----------\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again!\n";
        }
        Sleep(2000);
        system("cls");
    }
    
    return 0;
}
