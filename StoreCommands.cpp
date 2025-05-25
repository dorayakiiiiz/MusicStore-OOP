#include "StoreCommands.h"
#include "AuthService.h"
#include "utils.h"
#include "InputChecker.h"
#include "IController.h"
#include "ControllerFactory.h"
#include "ConsoleUI.h"
#include <iostream>

using std::tie;

// SignUpCommand implementation
SignUpCommand::SignUpCommand(shared_ptr<User>& user) : currentUser(user) {}

string SignUpCommand::getName() const {
    return "SIGN UP";
}

bool SignUpCommand::execute() {
    clearScreen();
    printFrame(0, 0, 120, 30);
    
    string header = "signUp";
    printHeader(header, (120 - header.length() * 2) / 2 - 15, 1);
    
    // Get role input with validation
    int role = getValidatedInput<int>(
        "Enter your role (1 for admin, 2 for customer): ",
        [](const string& prompt) {
            return InputChecker::validateInt(prompt, 10, 10, 1, 2);
        },
        10, 10
    );
    
    // Get username input with validation
    string username = getValidatedInput<string>(
        "Input username: ",
        [](const string& prompt) {
            return InputChecker::validateString(prompt, 10, 11);
        },
        10, 11
    );
    
    // Get password input with validation
    string password = getValidatedInput<string>(
        "Input password: ",
        [](const string& prompt) {
            return InputChecker::validateString(prompt, 10, 12);
        },
        10, 12
    );
    
    // Additional validation for admin registration
    if (Role::ADMIN == role) {
        string passkey = getInput("Input admin passkey: ", 10, 13);
        if (!Admin::isValidPasskey(passkey)) {
            printMessage("Invalid passkey. Please try again later!", 10, 14);
            sleepScreen();
            return true;
        }
    }

    // Register the new user
    bool success = AuthService::getInstance()->registerUser(username, password, static_cast<Role>(role));
    if (success) {
        printMessage("Sign up successfully!", 10, 13);
        sleepScreen();
    } else {
        printMessage("Username already exists. Please try again later!", 10, 14);
        sleepScreen();
    }
    
    return true;
}

// LoginCommand implementation
LoginCommand::LoginCommand(shared_ptr<User>& user) : currentUser(user) {}

string LoginCommand::getName() const {
    return "LOGIN";
}

bool LoginCommand::execute() {

    clearScreen();
    printFrame(0, 0, 120, 30);
    string header = "login";
    printHeader(header, (120 - header.length()*2) / 2 - 11, 1);

    // Get username input with validation
    string username = getValidatedInput<string>(
        "Input username: ",
        [](const string& prompt) {
            return InputChecker::validateString(prompt, 10, 10);
        },
        10, 10
    );

    // Get password input with validation
    string password = getValidatedInput<string>(
        "Input password: ",
        [](const string& prompt) {
            return InputChecker::validateString(prompt, 10, 11);
        },
        10, 11
    );

    // Attempt to authenticate the user
    currentUser = AuthService::getInstance()->loginUser(username, password);

    if (!currentUser) {
        printMessage("Invalid username or password. Please try again!", 10, 12);
        sleepScreen();
        return true;
    }

    // create the appropriate controller based on user role
    // and call the menu function of the controller
    Role role = currentUser->getRole();
    ControllerFactory factory;
    shared_ptr<IController> controller = factory.createController(role);

    if (controller) {
        printMessage("Login successfully! Welcome " + currentUser->getUsername() + "!", 10, 12);
        sleepScreen();
        clearScreen();
        controller->menu(currentUser);
        return true;
    }
    
    return true;
}

// ExitCommand implementation
string ExitCommand::getName() const {
    return "EXIT";
}

bool ExitCommand::execute() {
    printMessage("Exiting the application. Thank you for using our service!", 10, 25);
    sleepScreen();
    system("cls");
    return false;
}
