#include "ConsoleConfig.h"

#include "ConsoleConfig.h"

void ConsoleConfig::SetWindowsSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, (SHORT)(width - 1), (SHORT)(height - 1)};
    SetConsoleWindowInfo(hStdout, TRUE, &windowSize);
}

void ConsoleConfig::SetScreenBufferSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize = {width, height};
    SetConsoleScreenBufferSize(hStdout, newSize);
}

void ConsoleConfig::DisableResizeWindow() {
    HWND hwnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hwnd, FALSE);
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
    DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}

void ConsoleConfig::DisableCursor() {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void ConsoleConfig::FixConsoleWindow(SHORT width, SHORT height) {
    SetWindowsSize(width, height);
    SetScreenBufferSize(width, height);
    DisableResizeWindow();
    DisableCursor();
}