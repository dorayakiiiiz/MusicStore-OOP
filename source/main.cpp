/**
 * @mainpage Music Store Management System
 * 
 * @section intro_sec Introduction
 * 
 * This is a comprehensive Object-Oriented Music Store Management System built in C++.
 * The system provides functionality for both administrators and customers to manage
 * and purchase music items.
 * 
 * @section features_sec Key Features
 * 
 * - **User Management**: Support for Admin and Customer roles with authentication
 * - **Music Inventory**: Complete music catalog management with search capabilities
 * - **Shopping Cart**: Full shopping cart functionality with discount support
 * - **Order Processing**: Complete order management and purchase history
 * - **Sales Analytics**: Comprehensive sales reporting and statistics
 * - **Database Integration**: SQL Server integration for data persistence
 * 
 * @section architecture_sec System Architecture
 * 
 * The system follows object-oriented design principles and implements several design patterns:
 * - **Factory Pattern**: For creating appropriate controllers based on user roles
 * - **Strategy Pattern**: For discount calculations and search functionality
 * - **Command Pattern**: For menu operations and user actions
 * - **Singleton Pattern**: For service classes and database connections
 * - **Repository Pattern**: For data access abstraction
 * 
 * @section modules_sec Main Modules
 * 
 * - **Models**: Core business entities (User, Music, Order, Cart, Discount)
 * - **Services**: Business logic layer (AuthService, MusicService, OrderService, etc.)
 * - **Controllers**: User interface controllers (AdminController, CustomerController)
 * - **Database**: Data access layer with SQL Server integration
 * - **UI**: Console-based user interface components
 * - **Commands**: Command pattern implementation for user actions
 * 
 * @section authors_sec Authors
 * 
 * - **Trà Văn Sỹ (Leader)** - 23120197
 * - **Lê Hoàng Nhật Anh** - 23120209
 * 
 * @section course_info Course Information
 * 
 * - **Course**: Object-Oriented Programming
 * - **Class**: 23CTT3
 * - **Instructor**: Trần Duy Quang
 */


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
