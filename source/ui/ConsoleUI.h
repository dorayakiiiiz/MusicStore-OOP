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
    
    // Navigation menu with W/S/Enter
    static int selectMenu(const vector<std::string>& options, const string& header);
};

#endif // _CONSOLE_UI_H_