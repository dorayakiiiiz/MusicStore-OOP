#ifndef _COMMAND_INVOKER_H_
#define _COMMAND_INVOKER_H_

#include "Command.h"
#include <memory>
#include <vector>
#include <string>

using std::shared_ptr, std::vector;

/**
 * @brief Invoker class for executing commands
 * 
 * This class manages a collection of commands and executes them based on user choice
 */
class CommandInvoker {
private:
    vector<shared_ptr<Command>> _commands;
    string _headerText;
    
public:
    /**
     * @brief Constructor
     * @param headerText Text to display as header
     */
    CommandInvoker(const string& headerText);
    
    /**
     * @brief Register a command
     * @param command Command to add to the collection
     */
    void addCommand(shared_ptr<Command> command);
    
    /**
     * @brief Execute the command menu loop
     */
    void executeMenu();
};

#endif
