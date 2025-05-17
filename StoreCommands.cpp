#include "StoreCommands.h"
#include "AuthService.h"
#include "utils.h"
#include "InputValidator.h"
#include "Registry.h"
#include "IController.h"
#include "ControllerFactory.h"
#include <iostream>

using std::tie;

// SignUpCommand implementation
SignUpCommand::SignUpCommand(shared_ptr<User>& user) : currentUser(user) {}

string SignUpCommand::getName() const {
    return "Sign up";
}

bool SignUpCommand::execute() {
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
            return true;
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
    
    return true;
}

// LoginCommand implementation
LoginCommand::LoginCommand(shared_ptr<User>& user) : currentUser(user) {}

string LoginCommand::getName() const {
    return "Login";
}

bool LoginCommand::execute() {
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
        return true;
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
    
    return true;
}

// ExitCommand implementation
string ExitCommand::getName() const {
    return "Exit";
}

bool ExitCommand::execute() {
    printMessage("Exiting the application. Thank you for using our service!");
    sleepScreen();
    return false;
}
