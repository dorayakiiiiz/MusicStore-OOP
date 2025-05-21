/**
 * @file StoreApp.cpp
 * @brief Implementation file for the StoreApp class
 * 
 * @details Contains the main application logic, handling initialization,
 *          authentication, and the main program flow
 */

#include "StoreApp.h"
#include "utils.h"
#include "CommandInvoker.h"
#include "StoreCommands.h"

#include "IRepository.h"
#include "SQLDiscountRepository.h"
#include "SQLMusicRepository.h"
#include "SQLUserRepository.h"
#include "SQLOrderRepository.h"
#include "SQLSalesRecordRepository.h"

#include "MusicService.h"
#include "UserService.h"
#include "OrderService.h"
#include "DiscountService.h"
#include "SalesRecordService.h"
#include "CartService.h"
#include "AuthService.h"

#include "DatabaseConnector.h"
#include "ConsoleConfig.h"
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

    // Print welcome message
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