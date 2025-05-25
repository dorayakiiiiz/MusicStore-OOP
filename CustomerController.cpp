/************************************************************************************
 * @file CustomerController.cpp
 * @brief Implementation of the CustomerController class, which handles customer operations
 *        in a music store application.
 ************************************************************************************/

#include "CustomerController.h"
#include "CustomerUI.h"
#include "CommandInvoker.h"
#include "CustomerCommands.h"
#include "DiscountService.h"
#include "MusicService.h"
#include "CartService.h"
#include "OrderService.h"
#include "windows.h"
#include "utils.h"
#include "InputChecker.h"
#include "IRepository.h"
#include <memory>

using std::to_string, std::tie;

// Constructor for CustomerController
CustomerController::CustomerController() {}

// Implements the customer menu interface and all customer operations
void CustomerController::menu(shared_ptr<User>& currentUser) {
    // Create a shopping cart for the current session
    Cart cart;
    
    // Cast the User pointer to Customer type for customer-specific operations
    Customer* customer = dynamic_cast<Customer*>(currentUser.get());
    
    // Display welcome message
    clearScreen();
    CustomerUI::displayWelcomeMessage(customer->getUsername());
    
    // Create command invoker with menu title
    CommandInvoker invoker("CUSTOMER MENU");
    
    // Add all customer commands
    invoker.addCommand(std::make_shared<ViewPurchaseHistoryCommand>(currentUser));
    invoker.addCommand(std::make_shared<ViewMusicCommand>());
    invoker.addCommand(std::make_shared<SearchMusicCommand>());
    invoker.addCommand(std::make_shared<AddToCartCommand>(cart));
    invoker.addCommand(std::make_shared<RemoveFromCartCommand>(cart));
    invoker.addCommand(std::make_shared<CheckoutCommand>(cart, currentUser));
    invoker.addCommand(std::make_shared<CustomerLogoutCommand>(cart, currentUser));
    
    // Execute the command menu loop
    invoker.executeMenu();
}

