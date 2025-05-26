#ifndef _CONSOLEUI_H_
#define _CONSOLEUI_H_
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include "utils.h"

enum Color {
    BLACK       = 0,
    BLUE        = 1,
    GREEN       = 2,
    CYAN        = 3,
    RED         = 4,
    MAGENTA     = 5,
    YELLOW      = 6,
    WHITE       = 7,
    ORANGE      = 12,
    BRIGHT_WHITE = 15
};

class ConsoleUI {
public:
    static void gotoXY(short x, short y);

    static void setColor(Color fg, Color bg = BLACK);
    
    // Menu điều hướng bằng W/S/Enter
    static int selectMenu(const std::vector<std::string>& options, const std::string& header = "MENU");
};

#endif // _CONSOLEUI_H_