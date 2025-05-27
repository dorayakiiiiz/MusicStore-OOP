#include "ConnectionStatusDisplay.h"
#include "../ui/utils.h"

void ConnectionStatusDisplay::showConnectionProcess() {
    bool connected = false;
    DatabaseConnector* dbConnector = DatabaseConnector::getInstance();
    
    while (!connected) {
        clearScreen();
        printFrame(0, 0, 120, 30);
        
        // Show connecting message
        printFrame(30, 13, 60, 5);
        printMessage("CONNECTING TO DATABASE...", 45, 15);
        sleepScreen(1000);
        
        // Try to connect
        connected = dbConnector->connect();
        
        if (connected) {
            // Connection succeeded
            printFrame(30, 13, 60, 5);
            printMessage("CONNECTED TO DATABASE SUCCESSFULLY", 40, 15);
            sleepScreen(3000);  // Wait 3 seconds
            clearScreen(30, 13, 60, 4);  // Clear the success message
        } else {
            // Connection failed 
            printFrame(30, 13, 60, 5);
            printMessage("ERROR WHILE CONNECTING TO DATABASE, RETRY", 38, 15);
            sleepScreen(2000);  // Wait 2 seconds
            clearScreen(30, 13, 60, 4);  // Clear the error message
        }
    }
}