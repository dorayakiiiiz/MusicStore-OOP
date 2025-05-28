#ifndef _CONSOLE_UI_H_
#define _CONSOLE_UI_H_

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include "utils.h"
#include "../app/ConsoleConfig.h"

class ConsoleUI {
public:
    static void gotoXY(short x, short y);

    static void setColor(Color fg, Color bg = BLACK);
    
    // Menu điều hướng bằng W/S/Enter
    static int selectMenu(const std::vector<std::string>& options, const std::string& header = "MENU");
};

#endif // _CONSOLE_UI_H_