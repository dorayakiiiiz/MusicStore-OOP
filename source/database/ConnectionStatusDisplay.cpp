#include "ConnectionStatusDisplay.h"
#include "../ui/utils.h"

void ConnectionStatusDisplay::showConnectionProcess() {
    bool connected = false;
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    
    while (!connected) {
        clearScreen();
        printFrame(0, 0, 120, 30, LYELLOW);
        
        // Show connecting message
        printFrame(30, 13, 60, 5, LYELLOW);
        printMessage("CONNECTING TO DATABASE...", 45, 15, YELLOW);
        sleepScreen(1000);
        
        // Try to connect
        connected = dbConnector->connect();
        
        if (connected) {
            // Connection succeeded
            printFrame(0, 0, 120, 30, LGREEN);
            printFrame(30, 13, 60, 5, LGREEN);
            printMessage("CONNECTED TO DATABASE SUCCESSFULLY", 40, 15, LGREEN);
            sleepScreen(2000);  // Wait 3 seconds
            clearScreen(30, 13, 60, 4);  // Clear the success message
        } else {
            // Connection failed 
            printFrame(0, 0, 120, 30, LRED);
            printFrame(30, 13, 60, 5, LRED);
            printMessage("ERROR WHILE CONNECTING TO DATABASE, RETRY", 38, 15, LRED);
            sleepScreen(2000);  // Wait 2 seconds
            clearScreen(30, 13, 60, 4);  // Clear the error message
        }
    }
}