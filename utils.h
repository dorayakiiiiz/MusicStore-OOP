#ifndef _UI_H_
#define _UI_H_

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <limits>
#include <cfloat>
#include "ConsoleUI.h"
#include<fstream>
using std::string, std::vector, std::tuple, std::make_tuple, std::get, std::stoi, std::cout, std::cin;


/**
 * @brief Prints a formatted header with decorative elements
 * @param header The header text to display
 */
void printHeader(const string&);

/**
 * @brief Prints a message with a decorative symbol prefix
 * @param message The message to display
 */
void printMessage(const string&);


void printASCII(const string&, int, int);
/**
 * @brief Prints a horizontal line of dashes
 */
void printDashLine();

/**
 * @brief Clears the console screen
 */
void clearScreen();

/**
 * @brief Prints a message for repeating the last action
 */
void printRepeatMessage();


/**
 * @brief Pauses execution until user presses a key
 */
void pauseScreen();

/**
 * @brief Gets user input with a prompt
 * @param prompt The prompt to display to the user
 * @return The string input by the user
 */
string getInput(const string&);

/**
 * @brief Sleeps the program for a specified duration
 */
void sleepScreen();

/**
 * @brief Converts a string to lowercase
 * @param str The string to convert
 * @return The lowercase version of the input string
 */
string toLower(const string& str);


#endif