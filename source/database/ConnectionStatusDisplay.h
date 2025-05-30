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

    static void showConnectionProcess();
};

#endif