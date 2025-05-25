#include "utils.h"

#include <iostream>
#include <string>
#include <algorithm>
#include "fstream"
#include <windows.h>
using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi;
using std::to_string;

// Prints a formatted header with decorative elements
// Used to visually separate different sections of the UI
void printHeader(const string& header, int x, int y) {
    string fileName = "ascii/" + header + ".txt";
    string line = "";
    std::ifstream inFile;
    inFile.open(fileName);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            ConsoleUI::gotoXY(x, y++);
            cout << char(92) <<line << char(47) << '\n';
        }
    }
    cout << '\n';
    inFile.close();
}

// Prints a message with a decorative symbol prefix
// Used for displaying information to the user
void printMessage(const string& message) {
    cout << '\t' << char(175) << ' ' << message << '\n';
}

void printMenu(const string& header, int x, int y)
{
    string fileName = "";
    if(header == "WELCOME TO THE MUSIC STORE"){
        fileName = "ascii/musicStore.txt";
        x -= 4;
    }
    else if (header == "ADMIN MENU"){
        fileName = "ascii/adminMenu.txt";
        x += 14;
    }
    else{
        fileName = "ascii/customerMenu.txt";
        x += 5;
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
    inFile.close();
}

// Prints a horizontal line of dashes
// Used to visually separate content sections

// Prints a message for repeating the last action
void printRepeatMessage() {
    string instructions = "Press space to exit or any other key to continue...";
    int guideX = 64;
    int guideY = 26; 
    int guideW = 4 + instructions.size();
    int guideH = 3;
    printFrame(guideX, guideY, guideW, guideH);
    printInstructions(instructions, guideX + 1, guideY + 1);
}

void printFrame(int x, int y, int width, int height) {
    ConsoleUI::setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Màu trắng sáng

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

    ConsoleUI::setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Trả lại màu mặc định
}

void printFrameOptions(int x, int y, int width, int select) {
    ConsoleUI::setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Màu trắng sáng

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

    ConsoleUI::setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Trả lại màu mặc định
}

 void printInstructions(const string& instructions, int x, int y) {
    ConsoleUI::gotoXY(x, y);
    std::cout << char(94) << instructions << char(94);
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

void clearScreen(int x, int y, int width, int height) {
    for (int i = 0; i < height; ++i) {
        ConsoleUI::gotoXY(x, y + i);
        std::cout << std::string(width, ' ');
    }
}

// Pauses execution until user presses a key
void pauseScreen() {
    system("pause");
}

// Sleeps the program for a specified duration
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