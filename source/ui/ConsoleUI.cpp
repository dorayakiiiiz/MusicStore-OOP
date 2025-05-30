#include "ConsoleUI.h"

// Moves the console cursor to the specified (x, y) position.
void ConsoleUI::gotoXY(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the standard output handle.
    COORD pos = { x, y }; // Define the coordinates.
    SetConsoleCursorPosition(hConsole, pos); // Set the cursor position.
}

// Sets the text color (foreground and background) in the console.
void ConsoleUI::setColor(Color fg, Color bg) {
    WORD colorAttribute = (bg << 4) | fg; // Combine background and foreground colors.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttribute); // Set the text attribute.
}

// Displays a menu with the given options and header, allowing user selection.
int ConsoleUI::selectMenu(const vector<std::string>& options, const string& header) {
    // Initial position for the menu options.
    int x = 5;
    int y = 9 - options.size() / 2; // Center the menu vertically based on the number of options.
    int selected = 0; // Index of the currently selected option, defaults to the first option.

    // Define dimensions for the main frame.
    int frameX = 0, frameY = 0, frameW = 120, frameH = 30;
    // Calculate x-coordinate for centering the header text.
    int titleX = frameX + (frameW - header.length() * 2) / 2;

    // Define colors based on the header.
    Color fg;
    Color bg;
    if(header == "WELCOME TO THE MUSIC STORE"){
        fg = LYELLOW;
        bg = AQUA;
    }
    else if (header == "ADMIN MENU"){
        fg = AQUA;
        bg = LBLUE;
    }
    else{ // Default colors for other menus
        fg = LYELLOW;
        bg = YELLOW;
    }

    clearScreen(); // Clear the console screen.
    printFrame(frameX, frameY, frameW, frameH, fg); // Print the main border frame.

    // Print centered title.
    gotoXY(titleX, 6);
    printMenu(header, titleX, 6); // printMenu is assumed to be a utility function.

    // Print instructions for navigation.
    string instructions = "Use W/S to navigate and Enter to select";
    int guideX = 70; // X-coordinate for the instruction box.
    int guideY = 24; // Y-coordinate for the instruction box.
    int guideW = 4 + instructions.size(); // Width of the instruction box.
    int guideH = 3; // Height of the instruction box.
    printFrame(guideX, guideY, guideW, guideH); // Print frame for instructions.
    printInstructions(instructions, guideX + 2, guideY + 1, fg); // Print instruction text.

    // Main loop for menu interaction.
    while (true) {
        // Print frame around the selectable options.
        int optW = 6 + getMaxOptionsLength(options); // Calculate width needed for options frame.
        printFrameOptions(x, y, optW + 2, options.size(), fg); // printFrameOptions is assumed to be a utility function.

        // Print menu options, highlighting the selected one.
        for (int i = 0; i < options.size(); ++i) {
            gotoXY(x + 2, y + i * 2 + 1); // Position cursor for each option.
            if (i == selected)
                setColor(WHITE, bg); // Set highlight color for selected option.
            else
                setColor(WHITE, BLACK); // Set default color for non-selected options.
            cout << (i == selected ? ">> " : "   ") << options[i]; // Print option with selector.
            setColor(WHITE, BLACK); // Reset color to default.
        }

        int key = _getch(); // Get a character from keyboard input without waiting for Enter.
        if ('w' == key || 'W' == key) // Navigate up.
            selected = (selected - 1 + options.size()) % options.size(); // Move selection up, wrap around.
        else if ('s' == key || 'S' == key) // Navigate down.
            selected = (selected + 1) % options.size(); // Move selection down, wrap around.
        else if (13 == key) // Enter key pressed.
            return selected; // Return the index of the selected option.
    }
}