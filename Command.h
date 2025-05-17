#ifndef _COMMAND_H_
#define _COMMAND_H_

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
     */
    virtual void execute() = 0;
};

#endif