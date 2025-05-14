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

// Constructor - initializes the StoreApp by loading data from database
StoreApp::StoreApp() : controllerFactory(
    ControllerFactory(
        musicService,
        cartService,
        orderService,
        discountService,
        userService
    )) {
    initServices();
    loadData();
}

// Initializes all services used in the application
void StoreApp::initServices() {
    musicService = make_shared<MusicService>();
    userService = make_shared<UserService>();
    orderService = make_shared<OrderService>();
    cartService = make_shared<CartService>();
    discountService = make_shared<DiscountService>();
}



// Loads all data from database
void StoreApp::loadData() {
    try {
        // load data from database
        items = ReadDataFactory<Music>::createReadData()->readData();
        users = ReadDataFactory<shared_ptr<User>>::createReadData()->readData();
        orders = ReadDataFactory<Order>::createReadData()->readData();
        vouchers = ReadDataFactory<shared_ptr<Discount>>::createReadData()->readData();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Destructor - saves all data to files before exiting the application
StoreApp::~StoreApp() {
    saveData();
}

// Saves all data to files
void StoreApp::saveData() {
    try {
        // Save data to database
        SaveDataFactory<Music>::createSaveData()->saveData(items);
        SaveDataFactory<shared_ptr<User>>::createSaveData()->saveData(users);
        SaveDataFactory<Order>::createSaveData()->saveData(orders);
        SaveDataFactory<shared_ptr<Discount>>::createSaveData()->saveData(vouchers);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Handles the sign up process
void StoreApp::handleSignUp() {
    bool isValid;
    Error error;
    clearScreen();
    printHeader("SIGN UP");
    int role;
    string username, password;
    
    // Get role input with validation
    do {
        tie(isValid, role, error) = InputValidator::validateInt("Enter your role (1 for admin, 2 for customer): ", 1, 2);
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);
    
    // Get username input with validation
    do {
        tie(isValid, username, error) = InputValidator::validateString("Input username: ");
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);
    
    // Get password input with validation
    do {
        tie(isValid, password, error) = InputValidator::validateString("Input password: ");
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);
    
    // Additional validation for admin registration
    if (Role::ADMIN == role) {
        string passkey = getInput("Input admin passkey: ");
        if (!Admin::isValidPasskey(passkey)) {
            printMessage("Invalid passkey. Please try again later!");
            sleepScreen();
            return;
        }
    }

    // Register the new user
    bool success = auth.registerUser(users, username, password, static_cast<Role>(role));
    if (success) {
        printMessage("Sign up successfully!");
        sleepScreen();
    } else {
        printMessage("Username already exists. Please try again later!");
        sleepScreen();
    }
}

// Handles the login process
bool StoreApp::handleLogin(shared_ptr<User>& currentUser) {
    bool isValid;
    Error error;
    
    clearScreen();
    printHeader("LOGIN");
    string username, password;
    
    // Get username input with validation
    do {
        tie(isValid, username, error) = InputValidator::validateString("Input username: ");
        if (!isValid) {
            printMessage(error.message);
            sleepScreen();
            continue;
        }
    } while (!isValid);

    // Get password input with validation
    do {
        tie(isValid, password, error) = InputValidator::validateString("Input password: ");
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
    Role role = currentUser->getRole();
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
    shared_ptr<User> currentUser = nullptr;

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