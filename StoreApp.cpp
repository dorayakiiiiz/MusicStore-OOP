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

#include "IRepository.h"
#include "IUserRepository.h"
#include "IMusicRepository.h"
#include "IOrderRepository.h"
#include "IDiscountRepository.h"
#include "SQLDiscountRepository.h"
#include "SQLMusicRepository.h"
#include "SQLUserRepository.h"
#include "SQLOrderRepository.h"

#include "DatabaseConnector.h"
#include <exception>

#include <iostream>
#include <windows.h>

using std::tie;

// Constructor - initializes the StoreApp
StoreApp::StoreApp() {
    // Initialize services and register them with the Registry
    auto musicService = make_shared<MusicService>();
    auto userService = make_shared<UserService>();
    auto orderService = make_shared<OrderService>();
    auto discountService = make_shared<DiscountService>();
    auto cartService = make_shared<CartService>();
    auto authService = make_shared<AuthService>();

    Registry::addSingleton(musicService);
    Registry::addSingleton(userService);
    Registry::addSingleton(orderService);
    Registry::addSingleton(discountService);
    Registry::addSingleton(cartService);
    Registry::addSingleton(authService);

    // Initialize repositories
    shared_ptr<IMusicRepository> musicRepo = make_shared<SqlMusicRepository>();
    shared_ptr<IUserRepository> userRepo = make_shared<SqlUserRepository>();
    shared_ptr<IOrderRepository> orderRepo = make_shared<SqlOrderRepository>();
    shared_ptr<IDiscountRepository> discountRepo = make_shared<SqlDiscountRepository>();

    Registry::addSingleton(musicRepo);
    Registry::addSingleton(userRepo);
    Registry::addSingleton(orderRepo);
    Registry::addSingleton(discountRepo);

}

// destructor - cleans up the database connection
StoreApp::~StoreApp() {
    DatabaseConnector::cleanup();
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
    auto authService = Registry::getSingleton<AuthService>();
    bool success = authService->registerUser(username, password, static_cast<Role>(role));
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
    auto authService = Registry::getSingleton<AuthService>();
    currentUser = authService->loginUser(username, password);

    if (!currentUser) {
        printMessage("Invalid username or password. Please try again!");
        sleepScreen();
        return false;
    }

    // create the appropriate controller based on user role
    // and call the menu function of the controller
    Role role = currentUser->getRole();
    ControllerFactory factory;
    shared_ptr<IController> controller = factory.createController(role);

    if (controller) {
        printMessage("Login successfully! Welcome " + currentUser->getUsername() + "!");
        sleepScreen();
        clearScreen();
        controller->menu(currentUser);
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