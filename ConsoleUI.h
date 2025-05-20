#ifndef _CONSOLEUI_H_
#define _CONSOLEUI_H_
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include "utils.h"

class ConsoleUI {
public:
    static void gotoXY(short x, short y);

    static void setColor(WORD color);
    
    // Menu điều hướng bằng W/S/Enter
    static int selectMenu(const std::vector<std::string>& options, const std::string& header = "MENU");
};

#endif // _CONSOLEUI_H_