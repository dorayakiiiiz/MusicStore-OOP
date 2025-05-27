#ifndef _COMMAND_INVOKER_H_
#define _COMMAND_INVOKER_H_

#include "Command.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @brief Invoker class for executing commands
 * 
 * This class manages a collection of commands and executes them based on user choice
 */
class CommandInvoker {
private:
    std::vector<std::shared_ptr<Command>> commands;
    std::string headerText;
    
public:
    /**
     * @brief Constructor
     * @param headerText Text to display as header
     */
    CommandInvoker(const std::string& headerText);
    
    /**
     * @brief Register a command
     * @param command Command to add to the collection
     */
    void addCommand(std::shared_ptr<Command> command);
    
    /**
     * @brief Execute the command menu loop
     */
    void executeMenu();
};

#endif
