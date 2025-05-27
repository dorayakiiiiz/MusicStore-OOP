/**
 * @file StoreApp.cpp
 * @brief Implementation file for the StoreApp class
 * 
 * @details Contains the main application logic, handling initialization,
 *          authentication, and the main program flow
 */

#include "StoreApp.h"
#include "../commands/CommandInvoker.h"
#include "../commands/StoreCommands.h"
#include "../ui/utils.h"
#include "../ui/ConsoleUI.h"
#include "../database/DatabaseConnector.h"
#include "ConsoleConfig.h"

#include "../database/IRepository.h"
#include "../database/SQLDiscountRepository.h"
#include "../database/SQLMusicRepository.h"
#include "../database/SQLUserRepository.h"
#include "../database/SQLOrderRepository.h"
#include "../database/SQLSalesRecordRepository.h"
#include "../database/ConnectionStatusDisplay.h"

#include "../services/MusicService.h"
#include "../services/UserService.h"
#include "../services/OrderService.h"
#include "../services/DiscountService.h"
#include "../services/SalesRecordService.h"
#include "../services/CartService.h"
#include "../services/AuthService.h"

#include <iostream>
#include <windows.h>



// Constructor 
StoreApp::StoreApp() {}

// destructor - cleans up the database connection
StoreApp::~StoreApp() {
    DatabaseConnector::cleanup();
}

// Main application loop
void StoreApp::run() {
    // Set console 
    ConsoleConfig::FixConsoleWindow();

    // Initialize database connection with UI feedback
    ConnectionStatusDisplay::showConnectionProcess();

    // Create user session
    shared_ptr<User> currentUser = nullptr;

    // Create command invoker with menu title
    CommandInvoker invoker("WELCOME TO THE MUSIC STORE");
    
    // Add all store commands
    invoker.addCommand(std::make_shared<SignUpCommand>(currentUser));
    invoker.addCommand(std::make_shared<LoginCommand>(currentUser));
    invoker.addCommand(std::make_shared<ExitCommand>());
    
    // Execute the command menu loop
    invoker.executeMenu();
}