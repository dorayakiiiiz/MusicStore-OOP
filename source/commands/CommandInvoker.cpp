#include "CommandInvoker.h"
#include "../ui/utils.h"
#include "../ui/InputChecker.h"
#include "../ui/ConsoleUI.h"

// Constructor with header text
CommandInvoker::CommandInvoker(const std::string& headerText) : _headerText(headerText) {}

// Add a command to the collection
void CommandInvoker::addCommand(std::shared_ptr<Command> command) {
    _commands.push_back(command);
}

// Execute the command menu loop
void CommandInvoker::executeMenu() {
    while (true) {
        std::vector<std::string> options;
        for (const auto& command : _commands) {
            options.push_back(command->getName());
        }

        int selected = ConsoleUI::selectMenu(options, _headerText);
        bool continueLoop = _commands[selected]->execute();
        if (!continueLoop) {
            break;
        }
    }
}
