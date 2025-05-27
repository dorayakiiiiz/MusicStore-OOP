/**
 * @file main.cpp
 * @brief Main entry point for the Music Store application
 * 
 * @details Creates and initializes the StoreApp object and starts the application
 */

#include "app/StoreApp.h"

/**
 * @brief The main entry point of the application
 * 
 * @details Creates a StoreApp instance and runs the application
 * @return int Exit code (0 for successful execution)
 */
int main() {

    
    // Create an instance of the StoreApp with the authentication service
    StoreApp app;

    // Start the application's main execution loop
    app.run();

    // Return successful exit code
    return 0;
}
