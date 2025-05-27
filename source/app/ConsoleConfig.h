#ifndef _CONSOLECONFIG_H_
#define _CONSOLECONFIG_H_
#include <windows.h>

class ConsoleConfig {
public:
    // Đặt kích thước cửa sổ console
    static void SetWindowsSize(SHORT width, SHORT height);

    // Đặt kích thước buffer màn hình console
    static void SetScreenBufferSize(SHORT width, SHORT height);

    // Vô hiệu hóa resize cửa sổ và các nút thu/phóng
    static void DisableResizeWindow();

    // Ẩn con trỏ nháy trên console
    static void DisableCursor();

    // Thiết lập toàn bộ console: kích thước, buffer, khóa resize, ẩn con trỏ
    static void FixConsoleWindow(SHORT width = 120, SHORT height = 30);

};

#endif // _CONSOLECONFIG_H_