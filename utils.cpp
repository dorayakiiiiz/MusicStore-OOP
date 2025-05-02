#include "utils.h"

#include <iostream>
#include <string>
using std::cout, std::cin, std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi;
using std::to_string;
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
    for (int i = 1; i < 50; ++i) {
        cout << (char)205;
    }
    cout << '\n';
}

string getInput(const string& prompt) {
    cout << (char)16 << ' ' << prompt;
    string input; getline(cin, input);
    return input;
}

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    system("pause");
}

tuple <bool, int, Error> getIntInput(string prompt, int min, int max) {
    Error error = {0, ""};
    string input = getInput(prompt);
    if (input.empty()) {
        error.code = 1;
        error.message = "Input cannot be empty!";
        return make_tuple(false, -1, error);
    }
    try {
        int choice = stoi(input);
        if (choice < min || choice > max) {
            error.code = 2;
            error.message = "Input out of range!";
            return make_tuple(false, -1, error);
        }
        return make_tuple(true, choice, error);
    } catch (const std::invalid_argument&) {
        error.code = 3;
        error.message = "Invalid input! Please enter a valid number.";
        return make_tuple(false, -1, error);
    }
}

tuple <bool, float, Error> getFloatInput(string prompt, float min, float max) {
    Error error = {0, ""};
    string input = getInput(prompt);
    if (input.empty()) {
        error.code = 1;
        error.message = "Input cannot be empty!";
        return make_tuple(false, -1.0f, error);
    }
    try {
        float choice = stof(input);
        if (choice < min || choice > max) {
            error.code = 2;
            error.message = "Input out of range!";
            return make_tuple(false, -1.0f, error);
        }
        return make_tuple(true, choice, error);
    } catch (const std::invalid_argument&) {
        error.code = 3;
        error.message = "Invalid input! Please enter a valid number.";
        return make_tuple(false, -1.0f, error);
    }
}

tuple <bool, string, Error> getStringInput(string prompt, vector<string> option) {
    Error error = {0, ""};
    string input = getInput(prompt);
    if (input.empty()) {
        error.code = 1;
        error.message = "Input cannot be empty!";
        return make_tuple(false, "", error);
    }
    if (option.size() > 0) {
        for (const auto& opt : option) {
            if (input == opt) {
                return make_tuple(true, input, error);
            }
        }
        error.code = 2;
        error.message = "Invalid option! Please try again.";
        return make_tuple(false, "", error);
    }
    return make_tuple(true, input, error);
}