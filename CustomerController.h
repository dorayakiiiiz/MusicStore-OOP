/**
 * @file CustomerController.h
 * @brief Header file for the CustomerController class
 * 
 * @details Defines the CustomerController class which handles customer operations
 *          including viewing music, searching, cart management, and checkout
 */

#ifndef _CUSTOMER_CONTROLLER_H_
#define _CUSTOMER_CONTROLLER_H_

#include "IController.h"

/**
 * @brief Controller class for customer-specific functionality
 * 
 * @details Handles all customer operations including browsing music, managing cart, and placing orders
 */
class CustomerController : public IController {
public:
    /**
     * @brief Constructor for CustomerController
     */
    CustomerController();
    
    /**
     * @brief Implements the customer menu interface and all customer operations
     * 
     * @param currentUser Reference to the currently logged-in user
     */
    void menu(shared_ptr<User>& currentUser) override;
};

#endif

