#include "CommandInvoker.h"
#include "utils.h"
#include "InputValidator.h"

// Constructor with header text
CommandInvoker::CommandInvoker(const std::string& headerText) : headerText(headerText) {}

// Add a command to the collection
void CommandInvoker::addCommand(std::shared_ptr<Command> command) {
    commands.push_back(command);
}

// Execute the command menu loop
void CommandInvoker::executeMenu() {
    while (true) {
        clearScreen();
        printHeader(headerText);
        
        // Display all available commands
        std::vector<std::string> options;
        for (const auto& command : commands) {
            options.push_back(command->getName());
        }
        printMenu(options);
        
        // Get user choice with validation
        int choice;
        bool isValid;
        Error error;
        
        do {
            std::tie(isValid, choice, error) = InputValidator::validateInt(
                "Enter your choice: ", 1, commands.size());
                
            if (!isValid) {
                printMessage(error.message);
                sleepScreen();
                continue;
            }
        } while (!isValid);
        
        // Execute the selected command
        bool continueLoop = commands[choice - 1]->execute();
        if (!continueLoop) {
            break; // Exit if command returns false
        }
    }
}
