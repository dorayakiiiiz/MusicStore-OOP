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
#include "Registry.h"

#include "IRepository.h"
#include "IUserRepository.h"
#include "IMusicRepository.h"
#include "IOrderRepository.h"
#include "IDiscountRepository.h"
#include "SQLDiscountRepository.h"
#include "SQLMusicRepository.h"
#include "SQLUserRepository.h"
#include "SQLOrderRepository.h"

#include "MusicService.h"
#include "UserService.h"
#include "OrderService.h"
#include "DiscountService.h"
#include "CartService.h"
#include "AuthService.h"

#include "DatabaseConnector.h"
#include "ConsoleConfig.h"
#include <iostream>
#include <windows.h>

// Constructor - initializes the StoreApp
StoreApp::StoreApp() {
    // Initialize services and register them with the Registry
    auto musicService = make_shared<MusicService>();
    auto userService = make_shared<UserService>();
    auto orderService = make_shared<OrderService>();
    auto discountService = make_shared<DiscountService>();
    auto cartService = make_shared<CartService>();
    auto authService = make_shared<AuthService>();

    Registry::addSingleton(musicService);
    Registry::addSingleton(userService);
    Registry::addSingleton(orderService);
    Registry::addSingleton(discountService);
    Registry::addSingleton(cartService);
    Registry::addSingleton(authService);

    // Initialize repositories
    shared_ptr<IMusicRepository> musicRepo = make_shared<SqlMusicRepository>();
    shared_ptr<IUserRepository> userRepo = make_shared<SqlUserRepository>();
    shared_ptr<IOrderRepository> orderRepo = make_shared<SqlOrderRepository>();
    shared_ptr<IDiscountRepository> discountRepo = make_shared<SqlDiscountRepository>();

    Registry::addSingleton(musicRepo);
    Registry::addSingleton(userRepo);
    Registry::addSingleton(orderRepo);
    Registry::addSingleton(discountRepo);
}

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