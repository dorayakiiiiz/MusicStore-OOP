#include "StoreCommands.h"
#include "../ui/utils.h"
#include "../services/AuthService.h"
#include "../ui/InputChecker.h"
#include "../factories/ControllerFactory.h"
#include "../controllers/IController.h"
#include <conio.h>

using std::tie;

// SignUpCommand implementation
SignUpCommand::SignUpCommand(shared_ptr<User>& user) : _currentUser(user) {}

string SignUpCommand::getName() const {
    return "SIGN UP";
}

bool SignUpCommand::execute() {
    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30, LYELLOW);
        
        string header = "signUp";
        printHeader(header, (120 - header.length() * 2) / 2 - 15, 1, AQUA);
        
        printFrame(27, 7, 66, 3, LYELLOW);
        ConsoleUI::setColor(LAQUA);
        ConsoleUI::gotoXY(34, 8);
        cout << "ENTER YOUR ROLE (1 FOR ADMIN, 2 FOR CUSTOMER)  : ";
        ConsoleUI::setColor(WHITE);
        
        // Get role input with validation
        int role = getValidatedInput<int>(
            "ENTER YOUR ROLE (1 FOR ADMIN, 2 FOR CUSTOMER): ",
            [](const string& prompt) {
                return InputChecker::checkInt(prompt, 34, 8, 1, 2);
            },
            34, 8
        );

        
        printFrameOptions(30, 11, 60, 4 - role, LYELLOW);
        ConsoleUI::setColor(LAQUA);
        ConsoleUI::gotoXY(32, 12);
        cout << "INPUT USERNAME       : ";
        ConsoleUI::gotoXY(32, 14);
        cout << "INPUT PASSWORD       : ";

        if(1 == role){
            ConsoleUI::gotoXY(32, 16);
            cout << "INPUT ADMIN PASSKEY  : ";
        }
        
        // Get username input with validation
        string username = getValidatedInput<string>(
            "INPUT USERNAME     : ",
            [](const string& prompt) {
                return InputChecker::checkString(prompt, 32, 12);
            },
            32, 12
        );
        
        // Get password input with validation
        string password = getValidatedInput<string>(
            "INPUT PASSWORD     : ",
            [](const string& prompt) {
                return InputChecker::checkString(prompt, 32, 14);
            },
            32, 14
        );
        
        // Additional validation for admin registration
        if (Role::ADMIN == role) {
            ConsoleUI::setColor(LAQUA);
            string passkey = getInput("INPUT ADMIN PASSKEY: ", 32, 16);
            if (!Admin::isValidPasskey(passkey)) {
                printFrame(30, 20, 60, 3, LRED);
                printMessage("INVALID PASSKEY. PLEASE TRY AGAIN LATER!", 38, 21, LRED);
                printRepeatMessage(107, 1, "CONTINUE", LGREEN);
                printRepeatMessage(2, 1, "EXIT", LRED);
                char repeat = _getch();
                if (27 == repeat) {
                    return true;
                }
                else if (13 == repeat){
                    continue;
                }
            }
        }

        // Register the new user
        bool success = AuthService::getInstance()->registerUser(username, password, static_cast<Role>(role));
        if (success) {
            printFrame(40, 20, 40, 5, LGREEN);
            printMessage("SIGN UP SUCCESSFULLY", 48, 22, LGREEN);
            sleepScreen(1200);
            return true;
        } else {
            printFrame(30, 20, 60, 3, LRED);
            printMessage("USERNAME ALREADY EXISTS. PLEASE TRY AGAIN LATER!", 34, 21, LRED);
            printRepeatMessage(107, 1, "CONTINUE", LGREEN);
            printRepeatMessage(2, 1, "EXIT", LRED);
            char repeat = _getch();
            if (27 == repeat) {
                return true;
            }
            else if (13 == repeat){
                continue;
            }
        }
    }
    
    return true;
}

// LoginCommand implementation
LoginCommand::LoginCommand(shared_ptr<User>& user) : _currentUser(user) {}

string LoginCommand::getName() const {
    return "LOGIN";
}

bool LoginCommand::execute() {
    while(true){
        clearScreen();
        printFrame(0, 0, 120, 30, LYELLOW);
        string header = "login";
        printHeader(header, (120 - header.length()*2) / 2 - 11, 1, AQUA);

        printFrameOptions(30, 10, 60, 2, LYELLOW);
        ConsoleUI::setColor(LAQUA);
        ConsoleUI::gotoXY(32, 11);
        cout << "INPUT USERNAME  : ";
        ConsoleUI::gotoXY(32, 13);
        cout << "INPUT PASSWORD  : ";
        ConsoleUI::setColor(WHITE);

        // Get username input with validation
        string username = getValidatedInput<string>(
            "INPUT USERNAME: ",
            [](const string& prompt) {
                return InputChecker::checkString(prompt, 32, 11);
            },
            32, 11
        );

        // Get password input with validation
        string password = getValidatedInput<string>(
            "INPUT PASSWORD: ",
            [](const string& prompt) {
                return InputChecker::checkString(prompt, 32, 13);
            },
            32, 13
        );

        // Attempt to authenticate the user
        _currentUser = AuthService::getInstance()->loginUser(username, password);

        if (!_currentUser) {
            printFrame(30, 16, 60, 3, LRED);
            printMessage("INVALID USERNAME OR PASSWORD. PLEASE TRY AGAIN!", 36, 17, LRED);
            printRepeatMessage(107, 1, "CONTINUE", LGREEN);
            printRepeatMessage(2, 1, "EXIT", LRED);
            char repeat = _getch();
            if (27 == repeat) {
                return true;
            }
            else if (13 == repeat){
                continue;
            }
        }

        // create the appropriate controller based on user role
        // and call the menu function of the controller
        Role role = _currentUser->getRole();
        ControllerFactory factory;
        shared_ptr<IController> controller = factory.createController(role);

        if (controller) {
            printFrame(30, 16, 60, 5, LGREEN);
            printMessage("LOGIN SUCCESSFULLY! WELCOME " + _currentUser->getUsername() + "!", 40, 18, LGREEN);
            sleepScreen(1200);
            clearScreen();
            controller->menu(_currentUser);
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
    printFrame(5, 22, 40, 6, LGREEN);
    ConsoleUI::gotoXY(9, 24);
    ConsoleUI::setColor(LGREEN);
    cout << "    EXITING THE APPLICATION\n";
    ConsoleUI::gotoXY(9, 25);
    cout << "THANK YOU FOR USING OUR SERVICE!";
    ConsoleUI::setColor(WHITE);
    sleepScreen(1500);
    system("cls");
    return false;
}
