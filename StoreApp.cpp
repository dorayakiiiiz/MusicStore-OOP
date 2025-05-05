/**
 * @file StoreApp.cpp
 * @brief Implementation file for the StoreApp class
 * 
 * @details Contains the main application logic, handling initialization,
 *          authentication, and the main program flow
 */

#include "StoreApp.h"
#include "utils.h"
#include "InputValidator.h"
#include "AuthService.h"
#include "IController.h"
#include "ControllerFactory.h"

#include "ReadData.h"
#include "ReadDataFactory.h"
#include "SaveData.h"
#include "SaveDataFactory.h"
#include "DatabaseConnector.h"
#include <exception>

#include <iostream>
#include <windows.h>

using std::tie;

// Constructor - initializes the StoreApp by loading data from files
StoreApp::StoreApp() :
    auth(),
    musicService(),
    userService(), 
    orderService(),
    cartService(),
    discountService(),
    controllerFactory(musicService, cartService, orderService, discountService, userService) {
    loadData();
}

// Loads all data from files
void StoreApp::loadData() {
    try {
        // Load music items from file
        items = ReadDataFactory<Music>::createReadData()->readData();
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Load user accounts from file
        users = ReadDataFactory<shared_ptr<IUser>>::createReadData()->readData();
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Load order history from file
        orders = ReadDataFactory<Order>::createReadData()->readData();
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Load discount vouchers from file
        vouchers = ReadDataFactory<shared_ptr<Discount>>::createReadData()->readData();
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}

// Destructor - saves all data to files before exiting the application
StoreApp::~StoreApp() {
    saveData();
}

// Saves all data to files
void StoreApp::saveData() {
    try {
        // Save music inventory to file
        SaveDataFactory<Music>::createSaveData()->saveData(items);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Save user accounts to file
        SaveDataFactory<shared_ptr<IUser>>::createSaveData()->saveData(users);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Save order history to file
        SaveDataFactory<Order>::createSaveData()->saveData(orders);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    try {
        // Save discount vouchers to file
        SaveDataFactory<shared_ptr<Discount>>::createSaveData()->saveData(vouchers);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}

// Handles the sign up process
void StoreApp::handleSignUp() {
    bool isValid;
    Error error;
    
    clearScreen();
    printHeader("SIGN UP");
    string role, username, password;
    vector<string> options = {"Admin", "Customer"};
    
    // Get role input with validation
    do {
        std::tie(isValid, role, error) = InputValidator::validateString("Enter your role (Admin/Customer): ", options);
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);
    
    // Get username input with validation
    do {
        std::tie(isValid, username, error) = InputValidator::validateString("Input username: ");
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);
    
    // Get password input with validation
    do {
        std::tie(isValid, password, error) = InputValidator::validateString("Input password: ");
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);
    
    // Additional validation for admin registration
    if ("Admin" == toLower(role)) {
        string passkey = getInput("Input admin passkey: ");
        if (!Admin::isValidPasskey(passkey)) {
            printMessage("Invalid passkey. Please try again later!");
            sleepScreen();
            return;
        }
    }

    // Register the new user
    bool success = auth.registerUser(users, username, password, role);
    if (success) {
        printMessage("Sign up successfully!");
        sleepScreen();
    } else {
        printMessage("Username already exists. Please try again later!");
        sleepScreen();
    }
}

// Handles the login process
bool StoreApp::handleLogin(shared_ptr<IUser>& currentUser) {
    bool isValid;
    Error error;
    
    clearScreen();
    printHeader("LOGIN");
    string username, password;
    
    // Get username input with validation
    do {
        std::tie(isValid, username, error) = InputValidator::validateString("Input username: ");
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);

    // Get password input with validation
    do {
        std::tie(isValid, password, error) = InputValidator::validateString("Input password: ");
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);

    // Attempt to authenticate the user
    currentUser = auth.loginUser(users, username, password);

    if (!currentUser) {
        printMessage("Invalid username or password. Please try again!");
        sleepScreen();
        return false;
    }

    // create the appropriate controller based on user role
    // and call the menu function of the controller
    string role = currentUser->getRole();
    shared_ptr<IController> controller = controllerFactory.createController(role);

    if (controller) {
        printMessage("Login successfully! Welcome " + currentUser->getUsername() + "!");
        sleepScreen();
        clearScreen();
        controller->menu(items, users, orders, vouchers, currentUser);
        return true;
    }
    
    return false;
}

// Main application loop
void StoreApp::run() {
    shared_ptr<IUser> currentUser = nullptr;

    while (true) {

        clearScreen();
        printHeader("WELCOME TO THE MUSIC STORE");
    
        // Display main menu options
        vector<string> options = {
            "Sign up",
            "Login",
            "Exit\n",
        };
        printMenu(options);
        
        // get user choice from the main menu
        int choice;
        bool isValid;
        Error error;    
        do {
            tie(isValid, choice, error) = InputValidator::validateInt("Enter your choice: ", 1, 7);
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);

        switch (choice) {
            case 1: // Sign up
                handleSignUp();
                break;
                
            case 2: // Login
                handleLogin(currentUser);
                break;
                
            case 3: // Exit
                printMessage("Exiting the application. Thank you for using our service!");
                sleepScreen();
                return;
                
            default:
                break;
        }
    }
}