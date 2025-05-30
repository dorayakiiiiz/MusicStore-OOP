#ifndef _CONSOLE_UI_H_
#define _CONSOLE_UI_H_

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include "utils.h"
#include "../app/ConsoleConfig.h"

/**
 * @brief Provides utility functions for creating a console-based user interface.
 */
class ConsoleUI {
public:
    /**
     * @brief Moves the console cursor to the specified coordinates.
     * @param x The x-coordinate (column).
     * @param y The y-coordinate (row).
     */
    static void gotoXY(short x, short y);

    /**
     * @brief Sets the foreground and background colors of the console text.
     * @param fg The foreground color.
     * @param bg The background color (defaults to BLACK).
     */
    static void setColor(Color fg, Color bg = BLACK);
    
    /**
     * @brief Displays a navigatable menu and returns the user's selection.
     * Allows navigation using 'W' (up), 'S' (down), and selection with 'Enter'.
     * @param options A vector of strings representing the menu options.
     * @param header The header text to display above the menu.
     * @return The index of the selected option in the `options` vector.
     */
    static int selectMenu(const std::vector<std::string>& options, const std::string& header);
};

#endif // _CONSOLE_UI_H_