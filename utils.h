#ifndef _UI_H_
#define _UI_H_

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <limits>
#include <cfloat>
using std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi, std::cout, std::cin;


// nên sửa class này lại ra design pattern mới

void printHeader(const string&);
void printMessage(const string&);
void printMenu(const vector<string>&);
void printDashLine();
void clearScreen();
void pauseScreen();
string getInput(const string&);

struct Error {
    int code;
    string message;
};

tuple <bool, int, Error> getIntInput(string prompt, int min = INT_MIN, int max = INT_MAX);
tuple <bool, float, Error> getFloatInput(string prompt, float min = -FLT_MAX, float max = FLT_MAX);
tuple <bool, string, Error> getStringInput(string prompt, vector<string> option = {});
#endif