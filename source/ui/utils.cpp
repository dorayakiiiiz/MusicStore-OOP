#include "utils.h"
#include "ConsoleUI.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi, std::to_string, std::ifstream;

// Prints a formatted header with decorative elements
// Used to visually separate different sections of the UI
void printHeader(const string& header, int x, int y, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    string fileName = "ascii/" + header + ".txt";
    string line = "";
    ifstream inFile;
    inFile.open(fileName);

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            ConsoleUI::gotoXY(x, y++);
            cout << line << '\n';
        }
    }
    cout << '\n';
    ConsoleUI::setColor(WHITE);
    inFile.close();
}

// Prints a message with a decorative symbol prefix
// Used for displaying information to the user
void printMessage(const string& message, int x, int y, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y);
    cout << char(175) << ' ' << message << '\n';
    ConsoleUI::setColor(WHITE);
}

void printMenu(const string& header, int x, int y)
{
    string fileName = "";
    if("WELCOME TO THE MUSIC STORE" == header){
        ConsoleUI::setColor(AQUA);
        fileName = "ascii/musicStore.txt";
        x += 18;
    }
    else if ("ADMIN MENU" == header){
        fileName = "ascii/adminMenu.txt";
        x += 14;
        ConsoleUI::setColor(LBLUE);
    }
    else{
        fileName = "ascii/customerMenu.txt";
        x -= 5;
        ConsoleUI::setColor(YELLOW);
    }

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
    ConsoleUI::setColor(WHITE);
    inFile.close();
}

// Prints a horizontal line of dashes
// Used to visually separate content sections

// Prints a message for repeating the last action
void printRepeatMessage(int x, int y, string instructions, Color fg, Color bg) {
    int guideW = 3 + instructions.size();
    int guideH = 4;

    printFrame(x, y, guideW, guideH, fg);
    printInstructions(instructions, x + 1, y + 1, fg);

    if("EXIT" == instructions){
        ConsoleUI::setColor(fg);
        ConsoleUI::gotoXY(x + 1, y + 2);
        cout << "(Esc)";
    }
    else if ("CONTINUE" == instructions) {
        ConsoleUI::setColor(fg);
        ConsoleUI::gotoXY(x + 1, y + 2);
        cout << "(Any key)";
    }
    else{
        ConsoleUI::setColor(fg);
        ConsoleUI::gotoXY(x + 1, y + 2);
        cout << "(Enter)";
    }

    ConsoleUI::setColor(WHITE);
}

void printFrame(int x, int y, int width, int height, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y); 
    cout << char(201); 
    for (int i = 1; i < width - 1; ++i) {
        cout << char(205); 
    }
    cout << char(187); 

    for (int i = 1; i < height - 1; ++i) {
        ConsoleUI::gotoXY(x, y + i); 
        cout << char(186); 
        ConsoleUI::gotoXY(x + width - 1, y + i); 
        cout << char(186); 
    }

    ConsoleUI::gotoXY(x, y + height - 1); 
    cout << char(200); 
    for (int i = 1; i < width - 1; ++i) {
        cout << char(205); 
    }
    cout << char(188); 
    ConsoleUI::setColor(WHITE);
}

void printFrameOptions(int x, int y, int width, int select, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y);
    cout << char(218); // ┌
    for (int j = 1; j < width - 1; ++j) cout << char(196); // ─
    cout << char(191); // ┐

    for (int i = 1; i < select; ++i) {
        int currY = y + i * 2;
        ConsoleUI::gotoXY(x, currY);
        cout << char(195); // ├
        for (int j = 1; j < width - 1; ++j) {
            cout << char(196); // ─
        }
        cout << char(180); // ┤
    }

    for(int i = 0; i < select; ++i) {
        int curY = y + i * 2 + 1;
        ConsoleUI::gotoXY(x, curY);
        cout << char(179); 
        ConsoleUI::gotoXY(x + width - 1, curY);
        cout << char(179); 
    }

    ConsoleUI::gotoXY(x, y + select * 2);
    cout << char(192); // └
    for (int j = 1; j < width - 1; ++j) {
        cout << char(196); // ─
    }
    cout << char(217); // ┘
    ConsoleUI::setColor(WHITE);
}

 void printInstructions(const string& instructions, int x, int y, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y);
    cout << instructions;
    ConsoleUI::setColor(WHITE);
 }

// Gets user input with a prompt
// Returns the string input by the user
string getInput(const string& prompt, int x, int y) {
    ConsoleUI::gotoXY(x, y);
    cout << (char)175 << ' ' << prompt;
    string input; getline(cin, input);
    ConsoleUI::setColor(WHITE);
    return input;
}

// Clears the console screen
void clearScreen() {
    system("cls");
}

void clearScreen(int x, int y, int width, int height) {
    ConsoleUI::setColor(WHITE);
    for (int i = 0; i < height; ++i) {
        ConsoleUI::gotoXY(x, y + i);
        cout << std::string(width, ' ');
    }
}

// Sleeps the program for a specified duration
void sleepScreen(int time) {
    Sleep(time);
}

int getMaxOptionsLength(const vector<string>& options) {
    int maxLength = 0;
    for (const auto& optionss : options) {
        maxLength = (maxLength > optionss.length()) ? maxLength : optionss.length();
    }
    return maxLength;
}

string toLower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}