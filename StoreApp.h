#ifndef _STORE_APP_H_
#define _STORE_APP_H_

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
     * @brief Initializes the application and its components
     * 
     * Sets up the database connection, initializes services, and registers them.
     */
    void initializeServices();

    /**
     * @brief Initializes the repositories for data access
     * 
     * Sets up the repositories for user, music, order, and discount data.
     */
    void initializeRepositories();
    
    /**
     * @brief Main application loop that handles user authentication and navigation
     */
    void run();
};

#endif