#include "ConsoleUI.h"

void ConsoleUI::gotoXY(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hConsole, pos);
}

void ConsoleUI::setColor(Color fg, Color bg) {
    WORD colorAttribute = (bg << 4) | fg;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttribute);
}


int ConsoleUI::selectMenu(const std::vector<std::string>& options, const std::string& header) {
    int x = 5;
    int y = 9 - options.size() / 2;
    int selected = 0;
    int frameX = 0, frameY = 0, frameW = 120, frameH = 30;
    int titleX = frameX + (frameW - header.length() * 2) / 2;

    Color fg;
    Color bg;
    if(header == "WELCOME TO THE MUSIC STORE"){
        fg = LRED;
        bg = RED;
    }
    else if (header == "ADMIN MENU"){
        fg = LAQUA;
        bg = LBLUE;
    }
    else{
        fg = LYELLOW;
        bg = YELLOW;
    }

    clearScreen();
    printFrame(frameX, frameY, frameW, frameH, fg);

    // In tiêu đề căn giữa
    gotoXY(titleX, 6);
    printMenu(header, titleX, 6);

    // In hướng dẫn
    string instructions = "Use W/S to navigate and Enter to select";
    int guideX = 70;
    int guideY = 24; // Dòng gần cuối nếu height = 30
    int guideW = 4 + instructions.size();
    int guideH = 3;
    printFrame(guideX, guideY, guideW, guideH);
    printInstructions(instructions, guideX + 2, guideY + 1, fg);

    while (true) {
        // In khung lựa chọnchọn
        int optW = 6 + getMaxOptionsLength(options);
        printFrameOptions(x, y, optW + 2, options.size(), fg);

        // In các lựa chọn menu, mỗi dòng chiếm đúng 1 khung option
        for (int i = 0; i < options.size(); ++i) {
            gotoXY(x + 2, y + i * 2 + 1); // In ra giữa khung
            if (i == selected)
                setColor(WHITE, bg); // Highlight
            else
                setColor(WHITE, BLACK); // Mặc định
            std::cout << (i == selected ? ">> " : "   ") << options[i];
            setColor(WHITE, BLACK);
        }

        int key = _getch();
        if (key == 'w' || key == 'W')
            selected = (selected - 1 + options.size()) % options.size();
        else if (key == 's' || key == 'S')
            selected = (selected + 1) % options.size();
        else if (13 == key)
            return selected;
    }
}
