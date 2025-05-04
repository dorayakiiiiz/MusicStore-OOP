#include "utils.h"

#include <iostream>
#include <string>
#include <windows.h>
using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi;
using std::to_string;

// Prints a formatted header with decorative elements
// Used to visually separate different sections of the UI
void printHeader(const string& header) {
    cout << '\n';
    // Add decorative heart symbols before the header text
    for (int i = 1; i <= 10; ++i) {
        cout << (char)3 << ' ';
    }
    cout << header;
    // Add decorative heart symbols after the header text
    for (int i = 1; i <= 10; ++i) {
        cout << ' ' << (char)3;
    }
    cout << '\n';
}

// Prints a message with a decorative symbol prefix
// Used for displaying information to the user
void printMessage(const string& message) {
    cout << (char)5 << ' ' << message << '\n';
}

// Prints a numbered menu of options
// Used to display choices to the user
void printMenu(const vector<string>& option) {
    for (int i = 0; i < option.size(); ++i) {
        cout << (char)4 << ' ' << i + 1 << ". " << option[i] << "\n";
    }
}

// Prints a horizontal line of dashes
// Used to visually separate content sections
void printDashLine() {
    for (int i = 1; i < 50; ++i) {
        cout << (char)205;
    }
    cout << '\n';
}

// Gets user input with a prompt
// Returns the string input by the user
string getInput(const string& prompt) {
    cout << (char)16 << ' ' << prompt;
    string input; getline(cin, input);
    return input;
}

// Clears the console screen
void clearScreen() {
    system("cls");
}

// Pauses execution until user presses a key
void pauseScreen() {
    system("pause");
}

// Sleeps the program for a specified duration
void sleepScreen() {
    Sleep(1000);
}

string toLower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}