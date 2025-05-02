#include "StoreApp.h"
#include "utils.h"
#include "AuthService.h"
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

        bool isValid;
        Error error;

        printHeader("WELCOME TO THE MUSIC STORE");

        vector<string> options = {
            "Sign up",
            "Login",
            "Exit\n",
        };
        printMenu(options);

        int choice;
        do {
            std::tie(isValid, choice, error) = getIntInput("Enter your choice: ", 1, 3);
            if (!isValid) {
                printMessage(error.message);
                Sleep(1000);
                continue;
            }
        } while (!isValid);

        switch (choice) {
            case 1: {
                system("cls");
                printHeader("SIGN UP");
                string role, username, password;
                vector<string> options = {"admin", "user"};
                do {
                    std::tie(isValid, role, error) = getStringInput("Enter your role (admin/user): ", options);
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);
                do {
                    std::tie(isValid, username, error) = getStringInput("Input username: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);
                
                do {
                    std::tie(isValid, password, error) = getStringInput("Input password: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);
                
                if (role == "admin") {
                    string passkey = getInput("Input admin passkey: ");
                    if (!Admin::isValidPasskey(passkey)) {
                        printMessage("Invalid passkey. Please try again later!");
                        Sleep(1000);
                        break;
                    }
                }

                bool success = auth.registerUser(users, username, password, role);
                if (success) {
                    printMessage("Sign up successfully!");
                    Sleep(1000);
                } else {
                    printMessage("Username already exists. Please try again later!");
                    Sleep(1000);
                }
                break;
            }
            case 2: {
                system("cls");
                printHeader("LOGIN");
                string username, password;
                bool isValid = true;
                do {
                    std::tie(isValid, username, error) = getStringInput("Input username: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                do {
                    std::tie(isValid, password, error) = getStringInput("Input password: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                currentUser = auth.loginUser(users, username, password);

                if (!currentUser) {
                    printMessage("Invalid username or password. Please try again!");
                    Sleep(1000);
                    break;
                }
                
                printMessage("Login successfully! Welcome " + currentUser->getUsername() + "!");
                Sleep(1000);
                system("cls");

                ControllerFactory::createController(currentUser->getRole())->menu(items, users, orders, vouchers, currentUser);

                break;
            }
            case 3: {
                printMessage("Exiting the application. Thank you for using our service!");
                return;
            }
            default: {

            }
        }
    }
}