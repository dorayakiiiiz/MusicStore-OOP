/**
 * @file DatabaseConnector.h
 * @brief Header file for the DatabaseConnector class
 * 
 * @details Defines the DatabaseConnector class which manages connections
 *          to the database or file storage system
 */

#ifndef _DATABASE_CONNECTOR_H_
#define _DATABASE_CONNECTOR_H_
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <iostream>
#include <string>
#include <vector>

using std::string;
    
/**
 * @brief Database connection manager
 * 
 * Handles connections to SQL Server databases using ODBC.
 * Provides methods to establish and manage a database connection.
 */
class DatabaseConnector {
private:
    // singleton instance
    static DatabaseConnector* instance; ///< Singleton instance of DatabaseConnector

    SQLHENV hEnv;       ///< ODBC environment handle
    SQLHDBC hDbc;       ///< ODBC connection handle
    bool connected;     ///< Connection state flag

    /**
     * @brief constructor (private)
     * 
     * Initializes a new DatabaseConnector instance with null handles.
     */
    DatabaseConnector();

public:
    /**
     * @brief Get the singleton instance
     * 
     * @return DatabaseConnector* The singleton instance
     */
    static DatabaseConnector* getInstance();

    /**
     * @brief Destructor
     */
    ~DatabaseConnector();

    /**
     * @brief Ensures the database is connected, reconnects if needed
     * 
     * @return true if connected or successfully reconnected
     */
    bool ensureConnected();

    /**
     * @brief Establishes a database connection
     * 
     * Connects to the SQL Server database using ODBC.
     * 
     * @return true if connection was successful, false otherwise
     */
    bool connect();
    
    /**
     * @brief Gets the active connection handle
     * 
     * @return SQLHDBC The current database connection handle
     */
    SQLHDBC getConnection() const;
    
    /**
     * @brief Checks if the database is connected
     * 
     * @return true if connected to the database, false otherwise
     */
    bool isConnected() const;
    
    /**
     * @brief Closes the database connection and releases resources
     */
    void disconnect();

    /**
     * @brief Executes a simple query to check if connection is alive
     *
     * @return true if connection is working properly
     */
    bool testConnection() const;

    /**
     * @brief Cleanup resources before program exit
     */
    static void cleanup();
};

#endif