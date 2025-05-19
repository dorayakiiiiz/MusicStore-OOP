#include "CommandInvoker.h"
#include "utils.h"
#include "InputValidator.h"
#include "ConsoleUI.h"

// Constructor with header text
CommandInvoker::CommandInvoker(const std::string& headerText) : headerText(headerText) {}

// Add a command to the collection
void CommandInvoker::addCommand(std::shared_ptr<Command> command) {
    commands.push_back(command);
}

// Execute the command menu loop
void CommandInvoker::executeMenu() {
    while (true) {
        // Lấy tên các command
        std::vector<std::string> options;
        for (const auto& command : commands) {
            options.push_back(command->getName());
        }

        int selected = ConsoleUI::selectMenu(options, headerText);
        bool continueLoop = commands[selected]->execute();
        if (!continueLoop) break;
    }
}
