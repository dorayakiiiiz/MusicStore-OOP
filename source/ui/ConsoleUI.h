#ifndef _CONSOLE_UI_H_
#define _CONSOLE_UI_H_

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include "utils.h"
#include "../app/ConsoleConfig.h"

enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    AQUA = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LBLUE = 9,
    LGREEN = 10,
    LAQUA = 11,
    LRED = 12,
    LPURPLE = 13,
    LYELLOW = 14,
    LWHITE = 15
};

class ConsoleUI {
public:
    static void gotoXY(short x, short y);

    static void setColor(Color fg, Color bg = BLACK);
    
    // Menu điều hướng bằng W/S/Enter
    static int selectMenu(const std::vector<std::string>& options, const std::string& header = "MENU");
};

#endif // _CONSOLE_UI_H_