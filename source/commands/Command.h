#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
using std::string;

/**
 * @brief Interface for the Command pattern
 * 
 * Defines the contract that all commands must follow
 */
class Command {
public:
    virtual ~Command() = default;
    
    /**
     * @brief Execute the command
     * 
     * @return bool True if execution should continue, false if the menu loop should exit
     */
    virtual bool execute() = 0;
    
    /**
     * @brief Get the name of the command for display in menus
     * @return std::string The display name of the command
     */
    virtual string getName() const = 0;
};

#endif