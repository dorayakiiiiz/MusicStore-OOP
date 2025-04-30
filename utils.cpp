#include "utils.h"

#include <iostream>
using std::cout, std::cin;

void printHeader(const string& header) {
    cout << '\n';
    for (int i = 1; i <= 10; ++i) {
        cout << (char)3 << ' ';
    }
    cout << header;
    for (int i = 1; i <= 10; ++i) {
        cout << ' ' << (char)3;
    }
    cout << '\n';
}

void printMessage(const string& message) {
    cout << (char)5 << ' ' << message << '\n';
}

void printMenu(const vector<string>& option) {
    for (int i = 0; i < option.size(); ++i) {
        cout << (char)4 << ' ' << i + 1 << ". " << option[i] << "\n";
    }
}

void printDashLine() {
    for (int i = 1; i < 20; ++i) {
        cout << (char)42 << ' ';
    }
    cout << '\n';
}

string getInput(const string& prompt) {
    cout << (char)16 << ' ' << prompt;
    string input; getline(cin, input);
    return input;
}