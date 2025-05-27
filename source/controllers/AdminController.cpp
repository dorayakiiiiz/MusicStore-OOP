/**
 * @file AdminController.cpp
 * @brief Implementation file for the AdminController class 
 * 
 * @details Contains implementations of admin operations including managing music inventory,
 * user management, and generating sales reports.
 */

#include "AdminController.h"
#include "../ui/AdminUI.h"
#include "../commands/CommandInvoker.h"
#include "../ui/utils.h"
#include "../commands/AdminCommands.h"

// Constructor for AdminController
AdminController::AdminController() {}

// Implements the admin menu interface and all administrative operations
void AdminController::menu(shared_ptr<User>& currentUser) {
    // Display welcome message
    clearScreen();
    AdminUI::displayWelcomeMessage(currentUser->getUsername());
    
    // Create command invoker with menu title
    CommandInvoker invoker("ADMIN MENU");
    
    // Add all admin commands
    invoker.addCommand(std::make_shared<ViewMusicListCommand>());
    invoker.addCommand(std::make_shared<AddNewItemsCommand>());
    invoker.addCommand(std::make_shared<RemoveItemsCommand>());
    invoker.addCommand(std::make_shared<UpdatePriceCommand>());
    invoker.addCommand(std::make_shared<ViewUsersCommand>());
    invoker.addCommand(std::make_shared<ViewAllPurchaseHistoriesCommand>()); // Updated command name
    invoker.addCommand(std::make_shared<DeleteUserCommand>(currentUser));
    invoker.addCommand(std::make_shared<ViewSalesStatisticsCommand>());
    invoker.addCommand(std::make_shared<AdminLogoutCommand>(currentUser));
    
    // Execute the command menu loop
    invoker.executeMenu();
}

