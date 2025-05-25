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
    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30);
        
        string header = "signUp";
        printHeader(header, (120 - header.length() * 2) / 2 - 15, 1);
        
        printFrame(25, 7, 65, 3);
        // Get role input with validation
        int role = getValidatedInput<int>(
            "Enter your role (1 for admin, 2 for customer): ",
            [](const string& prompt) {
                return InputChecker::validateInt(prompt, 27, 8, 1, 2);
            },
            27, 8
        );

        
        printFrameOptions(30, 11, 60, 4 - role);

        ConsoleUI::gotoXY(32, 12);
        cout << "Input username       : ";
        ConsoleUI::gotoXY(32, 14);
        cout << "Input password       : ";

        if(role == 1){
            ConsoleUI::gotoXY(32, 16);
            cout << "Input admin passkey  : ";
        }
        
        // Get username input with validation
        string username = getValidatedInput<string>(
            "Input username     : ",
            [](const string& prompt) {
                return InputChecker::validateString(prompt, 32, 12);
            },
            32, 12
        );
        
        // Get password input with validation
        string password = getValidatedInput<string>(
            "Input password     : ",
            [](const string& prompt) {
                return InputChecker::validateString(prompt, 32, 14);
            },
            32, 14
        );
        
        // Additional validation for admin registration
        if (Role::ADMIN == role) {
            string passkey = getInput("Input admin passkey: ", 32, 16);
            if (!Admin::isValidPasskey(passkey)) {
                printFrame(30, 20, 60, 3);
                printMessage("Invalid passkey. Please try again later!", 38, 21);
                printRepeatMessage(108, 1, "CONTINUE");
                printRepeatMessage(2, 1, "EXIT");
                char repeat = _getch();
                if (repeat == 27) {
                    return true;
                }
                else if (repeat == 13){
                    continue;
                }
            }
        }

        // Register the new user
        bool success = AuthService::getInstance()->registerUser(username, password, static_cast<Role>(role));
        if (success) {
            printFrame(40, 20, 40, 5);
            printMessage("SIGN UP SUCCESSFULLY", 48, 22);
            sleepScreen(1500);
            return true;
        } else {
            printFrame(30, 20, 60, 3);
            printMessage("Username already exists. Please try again later!", 36, 21);
            printRepeatMessage(108, 1, "CONTINUE");
            printRepeatMessage(2, 1, "EXIT");
            char repeat = _getch();
            if (repeat == 27) {
                return true;
            }
            else if (repeat == 13){
                continue;
            }
        }
    }
    
    return true;
}

// LoginCommand implementation
LoginCommand::LoginCommand(shared_ptr<User>& user) : currentUser(user) {}

string LoginCommand::getName() const {
    return "LOGIN";
}

bool LoginCommand::execute() {
    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30);
        string header = "login";
        printHeader(header, (120 - header.length()*2) / 2 - 11, 1);

        printFrameOptions(30, 10, 60, 2);
        ConsoleUI::gotoXY(32, 11);
        cout << "Input username  : ";
        ConsoleUI::gotoXY(32, 13);
        cout << "Input password  : ";

        // Get username input with validation
        string username = getValidatedInput<string>(
            "Input username: ",
            [](const string& prompt) {
                return InputChecker::validateString(prompt, 32, 11);
            },
            32, 11
        );

        // Get password input with validation
        string password = getValidatedInput<string>(
            "Input password: ",
            [](const string& prompt) {
                return InputChecker::validateString(prompt, 32, 13);
            },
            32, 13
        );

        // Attempt to authenticate the user
        currentUser = AuthService::getInstance()->loginUser(username, password);

        if (!currentUser) {
            printFrame(30, 16, 60, 3);
            printMessage("Invalid username or password. Please try again!", 36, 17);
            printRepeatMessage(108, 1, "CONTINUE");
            printRepeatMessage(2, 1, "EXIT");
            char repeat = _getch();
            if (repeat == 27) {
                return true;
            }
            else if (repeat == 13){
                continue;
            }
        }

        // create the appropriate controller based on user role
        // and call the menu function of the controller
        Role role = currentUser->getRole();
        ControllerFactory factory;
        shared_ptr<IController> controller = factory.createController(role);

        if (controller) {
            printFrame(30, 16, 60, 5);
            printMessage("LOGIN SUCCESSFULLY! WELCOME " + currentUser->getUsername() + "!", 40, 18);
            sleepScreen(1500);
            clearScreen();
            controller->menu(currentUser);
            return true;
        }
    }
    return true;
}

// ExitCommand implementation
string ExitCommand::getName() const {
    return "EXIT";
}

bool ExitCommand::execute() {
    printFrame(5, 22, 40, 6);
    ConsoleUI::gotoXY(7, 24);
    cout << "    EXITING THE APPLICATION\n";
    ConsoleUI::gotoXY(7, 25);
    cout << "THANK YOU FOR USING OUR SERVICE!";
    sleepScreen(1500);
    system("cls");
    return false;
}
