#include "UI.h"

#include <iostream>
using std::cout, std::cin;


void UI::displayMenu(const vector<string>& option) {
    for (int i = 0; i < option.size(); ++i) {
        cout << option[i] << "\n";
    }
}

string UI::getInput(const string& prompt) {
    cout << prompt;
    string input; getline(cin, input);
    return input;
}