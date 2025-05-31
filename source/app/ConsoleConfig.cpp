/**
 * @file ConsoleConfig.cpp
 * @brief Implementation file for the ConsoleConfig class.
 * 
 * @details This file contains the implementations for methods that configure
 *          the console window, such as setting its size, buffer size,
 *          disabling resizing, and hiding the cursor.
 */
#include "ConsoleConfig.h"

/**
 * @brief Sets the size of the console window.
 * @param width The desired width of the console window.
 * @param height The desired height of the console window.
 */
void ConsoleConfig::SetWindowsSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, (SHORT)(width - 1), (SHORT)(height - 1)};
    SetConsoleWindowInfo(hStdout, TRUE, &windowSize);
}

/**
 * @brief Sets the screen buffer size of the console.
 * @param width The desired width of the screen buffer.
 * @param height The desired height of the screen buffer.
 */
void ConsoleConfig::SetScreenBufferSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize = {width, height};
    SetConsoleScreenBufferSize(hStdout, newSize);
}

/**
 * @brief Disables the ability to resize the console window.
 * @details This also removes the minimize and maximize buttons from the window's system menu.
 */
void ConsoleConfig::DisableResizeWindow() {
    HWND hwnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hwnd, FALSE);
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
    DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}

/**
 * @brief Hides the console cursor.
 */
void ConsoleConfig::DisableCursor() {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/**
 * @brief Applies a fixed configuration to the console window.
 * @details This method sets the window size, screen buffer size, disables resizing, and hides the cursor.
 * @param width The desired width for the console window and buffer (default is 120).
 * @param height The desired height for the console window and buffer (default is 30).
 */
void ConsoleConfig::FixConsoleWindow(SHORT width, SHORT height) {
    SetWindowsSize(width, height);
    SetScreenBufferSize(width, height);
    DisableResizeWindow();
    DisableCursor();
}