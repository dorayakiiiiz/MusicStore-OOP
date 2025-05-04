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

// Constructor - initializes the application by loading all data from files
StoreApp::StoreApp() {
    try {
        // Load music items from file
        items = ReadDataFactory<Music>::createReadData()->readData("music_info.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Load user accounts from file
        users = ReadDataFactory<shared_ptr<IUser>>::createReadData()->readData("user_info.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Load order history from file
        orders = ReadDataFactory<Order>::createReadData()->readData("orders.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Load discount vouchers from file
        vouchers = ReadDataFactory<shared_ptr<IDiscount>>::createReadData()->readData("vouchers.txt");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    
}

// Destructor - saves all data to files before application termination
StoreApp::~StoreApp() {
    try {
        // Save music inventory to file
        SaveDataFactory<Music>::createSaveData()->saveData("music_info.txt", items);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Save user accounts to file
        SaveDataFactory<shared_ptr<IUser>>::createSaveData()->saveData("user_info.txt", users);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Save order history to file
        SaveDataFactory<Order>::createSaveData()->saveData("orders.txt", orders);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Save discount vouchers to file
        SaveDataFactory<shared_ptr<IDiscount>>::createSaveData()->saveData("vouchers.txt", vouchers);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}

// Main application execution loop that handles the authentication flow and redirects to appropriate controller
void StoreApp::run() {
    Authentication auth;
    shared_ptr<IUser> currentUser = nullptr;    
    while (1) {
        system("cls"); // Clear console screen

        bool isValid;
        Error error;

        printHeader("WELCOME TO THE MUSIC STORE");

        // Display main menu options
        vector<string> options = {
            "Sign up",
            "Login",
            "Exit\n",
        };
        printMenu(options);

        // Get user choice with validation
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
            case 1: { // Sign up flow
                system("cls");
                printHeader("SIGN UP");
                string role, username, password;
                vector<string> options = {"Admin", "Customer"};
                
                // Get role input with validation
                do {
                    std::tie(isValid, role, error) = getStringInput("Enter your role (Admin/Customer): ", options);
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);
                
                // Get username input with validation
                do {
                    std::tie(isValid, username, error) = getStringInput("Input username: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);
                
                // Get password input with validation
                do {
                    std::tie(isValid, password, error) = getStringInput("Input password: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);
                
                // Additional validation for admin registration
                if (role == "Admin") {
                    string passkey = getInput("Input admin passkey: ");
                    if (!Admin::isValidPasskey(passkey)) {
                        printMessage("Invalid passkey. Please try again later!");
                        Sleep(1000);
                        break;
                    }
                }

                // Register the new user
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
            case 2: { // Login flow
                system("cls");
                printHeader("LOGIN");
                string username, password;
                bool isValid = true;
                
                // Get username input with validation
                do {
                    std::tie(isValid, username, error) = getStringInput("Input username: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                // Get password input with validation
                do {
                    std::tie(isValid, password, error) = getStringInput("Input password: ");
                    if (!isValid) {
                        printMessage(error.message);
                        Sleep(1000);
                        continue;
                    }
                } while (!isValid);

                // Attempt to authenticate the user
                currentUser = auth.loginUser(users, username, password);

                if (!currentUser) {
                    printMessage("Invalid username or password. Please try again!");
                    Sleep(1000);
                    break;
                }
                
                printMessage("Login successfully! Welcome " + currentUser->getUsername() + "!");
                Sleep(1000);
                system("cls");

                // Create appropriate controller based on user role and redirect to respective menu
                ControllerFactory::createController(currentUser->getRole())->menu(items, users, orders, vouchers, currentUser);

                break;
            }
            case 3: { // Exit application
                printMessage("Exiting the application. Thank you for using our service!");
                return;
            }
            default: {
                // This should not be reached due to input validation
            }
        }
    }
}