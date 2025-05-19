#include "utils.h"

#include <iostream>
#include <string>
#include "fstream"
#include <windows.h>
using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi;
using std::to_string;

// Prints a formatted header with decorative elements
// Used to visually separate different sections of the UI
void printHeader(const string& header, int x, int y) {
    string fileName = header + ".txt";
    string line = "";
    std::ifstream inFile;
    inFile.open(fileName);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            ConsoleUI::gotoXY(x, y++);
            cout << (char)92 <<line << (char)47 << '\n';
        }
    }
    cout << '\n';
    inFile.close();
}

// Prints a message with a decorative symbol prefix
// Used for displaying information to the user
void printMessage(const string& message) {
    cout << '\t' << (char)175 << ' ' << message << '\n';
}

void printASCII(const string& header, int x, int y)
{
    string fileName = header + ".txt";
    string line = "";
    std::ifstream inFile;
    inFile.open(fileName);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            ConsoleUI::gotoXY(x, y++);
            cout << line << '\n';
        }
    }
    cout << '\n';
    inFile.close();
}

// Prints a horizontal line of dashes
// Used to visually separate content sections
void printDashLine() {
    cout << '\t';
    for (int i = 1; i < 50; ++i) {
        cout << (char)205;
    }
    cout << '\n';
}

// Prints a message for repeating the last action
void printRepeatMessage() {
    cout << "\tPress space to exit or any other key to continue...\n";
}

// Gets user input with a prompt
// Returns the string input by the user
string getInput(const string& prompt) {
    cout << '\t' << (char)16 << ' ' << prompt;
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
    Sleep(500);
}

string toLower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}