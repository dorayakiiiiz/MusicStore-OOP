#include "ConsoleUI.h"

void ConsoleUI::gotoXY(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hConsole, pos);
}

void ConsoleUI::setColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ConsoleUI::printFrame(int x, int y, int width, int height) {
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Màu trắng sáng

    gotoXY(x, y); std::cout << char(201); // góc trên trái
    for (int i = 1; i < width - 1; ++i) std::cout << char(205); // cạnh trên
    std::cout << char(187); // góc trên phải

    for (int i = 1; i < height - 1; ++i) {
        gotoXY(x, y + i); std::cout << char(186); // cạnh trái
        gotoXY(x + width - 1, y + i); std::cout << char(186); // cạnh phải
    }

    gotoXY(x, y + height - 1); std::cout << char(200); // góc dưới trái
    for (int i = 1; i < width - 1; ++i) std::cout << char(205); // cạnh dưới
    std::cout << char(188); // góc dưới phải

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Trả lại màu mặc định
}

int ConsoleUI::selectMenu(const std::vector<std::string>& options, const std::string& header, int x, int y) {
    int selected = 0;
    int frameX = 1, frameY = 1, frameW = 119, frameH = 29;
    int titleX = frameX + (frameW - header.length() - 30) / 2; // căn giữa tiêu đề
    while (true) {
        system("cls");
        printFrame(frameX, frameY, frameW, frameH); // Vẽ khung mỗi lần lặp

        // In tiêu đề căn giữa
        gotoXY(titleX, y - 2);
        printASCII(header, titleX, y - 2);

        // In các lựa chọn menu
        for (int i = 0; i < options.size(); ++i) {
            gotoXY(x, y + i);
            if (i == selected)
                setColor(BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            else
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << (i == selected ? "> " : "  ") << options[i];
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        int key = _getch();
        if (key == 'w' || key == 'W')
            selected = (selected - 1 + options.size()) % options.size();
        else if (key == 's' || key == 'S')
            selected = (selected + 1) % options.size();
        else if (key == 13)
            return selected;
    }
}