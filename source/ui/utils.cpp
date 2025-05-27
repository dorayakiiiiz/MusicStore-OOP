#include "utils.h"
#include "ConsoleUI.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi;
using std::to_string;

// Prints a formatted header with decorative elements
// Used to visually separate different sections of the UI
void printHeader(const string& header, int x, int y, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    string fileName = "ascii/" + header + ".txt";
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
    ConsoleUI::setColor(Color::WHITE);
    inFile.close();
}

// Prints a message with a decorative symbol prefix
// Used for displaying information to the user
void printMessage(const string& message, int x, int y, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y);
    cout << char(175) << ' ' << message << '\n';
    ConsoleUI::setColor(Color::WHITE);
}

void printMenu(const string& header, int x, int y)
{
    string fileName = "";
    if(header == "WELCOME TO THE MUSIC STORE"){
        fileName = "ascii/musicStore.txt";
        x += 18;
        ConsoleUI::setColor(Color::LRED);
    }
    else if (header == "ADMIN MENU"){
        fileName = "ascii/adminMenu.txt";
        x += 14;
        ConsoleUI::setColor(Color::LBLUE);
    }
    else{
        fileName = "ascii/customerMenu.txt";
        x -= 5;
        ConsoleUI::setColor(Color::YELLOW);
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
    ConsoleUI::setColor(Color::WHITE);
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

    if(instructions == "EXIT"){
        ConsoleUI::setColor(fg);
        ConsoleUI::gotoXY(x + 1, y + 2);
        cout << "(Esc)";
    }
    else if (instructions == "CONTINUE") {
        ConsoleUI::setColor(fg);
        ConsoleUI::gotoXY(x + 1, y + 2);
        cout << "(Any key)";
    }
    else{
        ConsoleUI::setColor(fg);
        ConsoleUI::gotoXY(x + 1, y + 2);
        cout << "(Enter)";
    }

    ConsoleUI::setColor(Color::WHITE);
}

void printFrame(int x, int y, int width, int height, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y); std::cout << char(201); // góc trên trái
    for (int i = 1; i < width - 1; ++i) std::cout << char(205); // cạnh trên
    std::cout << char(187); // góc trên phải

    for (int i = 1; i < height - 1; ++i) {
        ConsoleUI::gotoXY(x, y + i); std::cout << char(186); // cạnh trái
        ConsoleUI::gotoXY(x + width - 1, y + i); std::cout << char(186); // cạnh phải
    }

    ConsoleUI::gotoXY(x, y + height - 1); std::cout << char(200); // góc dưới trái
    for (int i = 1; i < width - 1; ++i) std::cout << char(205); // cạnh dưới
    std::cout << char(188); // góc dưới phải
    ConsoleUI::setColor(Color::WHITE);
}

void printFrameOptions(int x, int y, int width, int select, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    // Vẽ cạnh trên của ô đầu tiên
    ConsoleUI::gotoXY(x, y);
    std::cout << char(218); // ┌
    for (int j = 1; j < width - 1; ++j) std::cout << char(196); // ─
    std::cout << char(191); // ┐

    // Các cạnh giữa (sát nhau)
    for (int i = 1; i < select; ++i) {
        int currY = y + i * 2;
        ConsoleUI::gotoXY(x, currY);
        std::cout << char(195); // ├
        for (int j = 1; j < width - 1; ++j) std::cout << char(196); // ─
        std::cout << char(180); // ┤
    }

    // Cạnh giữa có ô được chọn
    for(int i = 0; i < select; ++i) {
        int curY = y + i * 2 + 1;
        ConsoleUI::gotoXY(x, curY);
        std::cout << char(179); 
        ConsoleUI::gotoXY(x + width - 1, curY);
        std::cout << char(179); 
    }

    // Cạnh dưới cuối cùng
    ConsoleUI::gotoXY(x, y + select * 2);
    std::cout << char(192); // └
    for (int j = 1; j < width - 1; ++j) std::cout << char(196); // ─
    std::cout << char(217); // ┘
    ConsoleUI::setColor(Color::WHITE);
}

 void printInstructions(const string& instructions, int x, int y, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y);
    std::cout << instructions;
    ConsoleUI::setColor(Color::WHITE);
 }

// Gets user input with a prompt
// Returns the string input by the user
string getInput(const string& prompt, int x, int y, Color fg, Color bg) {
    ConsoleUI::setColor(fg);
    ConsoleUI::gotoXY(x, y);
    cout << (char)175 << ' ' << prompt;
    string input; getline(cin, input);
    ConsoleUI::setColor(Color::WHITE);
    return input;
}

// Clears the console screen
void clearScreen() {
    system("cls");
}

void clearScreen(int x, int y, int width, int height) {
    ConsoleUI::setColor(Color::WHITE);
    for (int i = 0; i < height; ++i) {
        ConsoleUI::gotoXY(x, y + i);
        std::cout << std::string(width, ' ');
    }
}

// Sleeps the program for a specified duration
void sleepScreen(int time = 500) {
    Sleep(time);
}

void sleepScreen() {
    Sleep(500);
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