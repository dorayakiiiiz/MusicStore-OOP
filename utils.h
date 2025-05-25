#ifndef _UI_H_
#define _UI_H_

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <limits>
#include <functional>
#include <cfloat>
#include "ConsoleUI.h"
#include "InputChecker.h"
#include "Music.h"
#include<fstream>
using std::string, std::vector, std::tuple, std::make_tuple, std::get;
using std::stoi, std::cout, std::cin, std::function, std::tie;

/**
 * @brief Prints a formatted header with decorative elements
 * @param header The header text to display
 */
void printHeader(const string&, int, int);

/**
 * @brief Prints a message with a decorative symbol prefix
 * @param message The message to display
 */
void printMessage(const string&, int, int);


void printMenu(const string&, int, int);
/**
 * @brief Prints a horizontal line of dashes
 */


/**
 * @brief Clears the console screen
 */
void clearScreen();

void clearScreen(int x, int y, int width, int height);

/**
 * @brief Prints a message for repeating the last action
 */
void printRepeatMessage(int x, int y, string instructions);

void printFrame(int x, int y, int width, int height);
/**
 * @brief Prints a frame around a specified area
 * @param x The x-coordinate of the top-left corner
 * @param y The y-coordinate of the top-left corner
 * @param width The width of the frame
 * @param height The height of the frame
 */

void printFrameOptions(int x, int y, int width, int select);


/**
 * @brief Prints a frame around a specified area with options
 * @param x The x-coordinate of the top-left corner
 * @param y The y-coordinate of the top-left corner
 * @param width The width of the frame
 * @param select The number of options to display
 */

 void printInstructions(const string& instructions, int x, int y);

/**
 * @brief Gets user input with a prompt
 * @param prompt The prompt to display to the user
 * @return The string input by the user
 */
string getInput(const string&, int, int);

/**
 * @brief Sleeps the program for a specified duration
 */
void sleepScreen(int time);

void sleepScreen();

/**
 * @brief Converts a string to lowercase
 * @param str The string to convert
 * @return The lowercase version of the input string
 */
string toLower(const string& str);

/**
 * @brief Gets the maximum length of options in a vector
 * @param options The vector of options to check
 * @return The length of the longest option
 */
int getMaxOptionsLength(const vector<string>& options);


/**
 * @brief Validates user input based on a provided validation function
 * @param prompt The prompt to display to the user
 * @param validatorFunc The validation function to use
 * @return The validated input value
 */
template<typename T>
T getValidatedInput(const string& prompt, function<tuple<bool, T, Error>(const string&)> validatorFunc, int promptX, int promptY) {
    bool isValid;
    T value;
    Error error;

    do {
        clearScreen(promptX, promptY, prompt.size() + 8, 1);
        tie(isValid, value, error) = validatorFunc(prompt);
        if (!isValid) {
            printFrame(50, 25, error.message.size() + 4, 3);
            printMessage(error.message, 52, 26);
            printRepeatMessage(2, 1, "EXIT");
            printRepeatMessage(108, 1, "CONTINUE");
            char repeat = _getch();
            if (repeat == 27) { // ESC
                break;
            }
            clearScreen(50, 25, error.message.size() + 4, 3);
            clearScreen(2, 1, 7, 4);
            clearScreen(108, 1, 11, 4);
        }
    } while (!isValid);

    return value;
}

#endif