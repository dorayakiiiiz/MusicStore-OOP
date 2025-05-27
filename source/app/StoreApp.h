#ifndef _STORE_APP_H_
#define _STORE_APP_H_

#include "../services/AuthService.h"
#include "../controllers/IController.h"
#include "../factories/ControllerFactory.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @brief Main application class that manages the entire music store system
 */
class StoreApp {
public:
    /**
     * @brief Constructor - initializes the StoreApp
     */
    StoreApp();

    /**
     * @brief Destructor - cleans up resources before application exits
     */
    ~StoreApp();
    
    /**
     * @brief Main application loop that handles user authentication and navigation
     */
    void run();
};

#endif