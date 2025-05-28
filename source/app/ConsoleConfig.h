#ifndef _CONSOLECONFIG_H_
#define _CONSOLECONFIG_H_
#include <windows.h>

class ConsoleConfig {
public:
    // Set the window panel size
    static void SetWindowsSize(SHORT width, SHORT height);

    // Set console screen buffer size
    static void SetScreenBufferSize(SHORT width, SHORT height);

    // Disable window resizing and zoom buttons
    static void DisableResizeWindow();

    // Hide the console cursor
    static void DisableCursor();

    // Set the whole console: size, buffer, resize lock, hide cursor
    static void FixConsoleWindow(SHORT width = 120, SHORT height = 30);

};

#endif // _CONSOLECONFIG_H_