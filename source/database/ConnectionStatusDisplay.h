#ifndef _CONNECTION_STATUS_DISPLAY_H_
#define _CONNECTION_STATUS_DISPLAY_H_

#include "DatabaseConnector.h"
#include "../ui/ConsoleUI.h"
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

class ConnectionStatusDisplay {
public:
    /**
     * @brief Hiển thị UI kết nối database với thông báo phù hợp
     * 
     * @return bool Trạng thái kết nối (true nếu thành công)
     */
    static void showConnectionProcess();
};

#endif