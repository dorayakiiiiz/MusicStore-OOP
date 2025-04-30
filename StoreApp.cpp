#include "StoreApp.h"
#include "utils.h"
#include "Authentication.h"
#include "IController.h"
#include "ControllerFactory.h"

#include "ReadData.h"
#include "ReadDataFactory.h"
#include "SaveData.h"
#include "SaveDataFactory.h"

#include <iostream>
#include <windows.h>

StoreApp::StoreApp() {
    try {
        items = ReadDataFactory<Music>::createReadData()->readData("music_info.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        users = ReadDataFactory<shared_ptr<IUser>>::createReadData()->readData("user_info.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        orders = ReadDataFactory<Order>::createReadData()->readData("orders.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        vouchers = ReadDataFactory<shared_ptr<IDiscount>>::createReadData()->readData("vouchers.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    
}

StoreApp::~StoreApp() {
    try {
        SaveDataFactory<Music>::createSaveData()->saveData("music_info.txt", items);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        SaveDataFactory<shared_ptr<IUser>>::createSaveData()->saveData("user_info.txt", users);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        SaveDataFactory<Order>::createSaveData()->saveData("orders.txt", orders);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        SaveDataFactory<shared_ptr<IDiscount>>::createSaveData()->saveData("vouchers.txt", vouchers);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}

void StoreApp::run() {
    Authentication auth;
    shared_ptr<IUser> currentUser = nullptr;    
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
                cout << "\n---------- SIGN UP ----------\n";
                cout << "Choose your role (Admin/Customer): \n";
                string role = getInput("Input role: ");
                string username = getInput("Input username (no spaces): ");
                string password = getInput("Input password: ");
                
                if (role == "Admin") {
                    string passkey = getInput("Input admin passkey: ");
                    if (!AdminPasskey::isValid(passkey)) {
                        cout << "Invalid passkey. Please try again!\n";
                        break;
                    }
                }

                bool success = auth.registerUser(users, username, password, role);
                if (success) {
                    cout << "Sign up successfully!\n";
                } else {
                    cout << "Username already exists. Please try again!\n";
                }
                break;
            }
            case 2: {

                cout << "\n---------- LOGIN ----------\n";
                string username = getInput("Input username: ");
                string password = getInput("Input password: ");
                currentUser = auth.loginUser(users, username, password);

                if (!currentUser) {
                    cout << "Invalid username or password. Please try again!\n";
                    break;
                }
                
                cout << "Login successfully!\n";
                Sleep(1000);
                system("cls");

                ControllerFactory::createController(currentUser->getRole())->menu(items, users, orders, vouchers, currentUser);

                break;
            }
            case 3: {
                cout << "---------- GOODBYE! ----------\n";
                return;
            }
            default:
                cout << "Invalid choice. Please try again!\n";
        }
        Sleep(2500);
    }
}