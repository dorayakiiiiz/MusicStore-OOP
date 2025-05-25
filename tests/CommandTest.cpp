#include "gtest/gtest.h"
#include "../Command.h"
#include "../CommandInvoker.h"
#include <memory>
#include <string>

// Mock command class for testing
class MockCommand : public Command {
private:
    std::string name;
    bool* wasExecuted;
    bool returnValue;

public:
    MockCommand(const std::string& name, bool* wasExecuted, bool returnValue = true) 
        : name(name), wasExecuted(wasExecuted), returnValue(returnValue) {}

    std::string getName() const override {
        return name;
    }

    bool execute() override {
        *wasExecuted = true;
        return returnValue;
    }
};

class CommandTest : public ::testing::Test {
protected:
    bool commandExecuted;

    void SetUp() override {
        commandExecuted = false;
    }
};

// Test that commands can be executed
TEST_F(CommandTest, CommandExecution) {
    std::shared_ptr<Command> command = std::make_shared<MockCommand>("Test Command", &commandExecuted);
    
    EXPECT_FALSE(commandExecuted);
    bool result = command->execute();
    EXPECT_TRUE(commandExecuted);
    EXPECT_TRUE(result);
    
    EXPECT_EQ("Test Command", command->getName());
}

// Test that CommandInvoker can manage multiple commands
TEST_F(CommandTest, CommandInvokerAddCommand) {
    CommandInvoker invoker("Test Menu");
    
    bool cmd1Executed = false;
    bool cmd2Executed = false;
    
    auto command1 = std::make_shared<MockCommand>("Command 1", &cmd1Executed);
    auto command2 = std::make_shared<MockCommand>("Command 2", &cmd2Executed);
    
    invoker.addCommand(command1);
    invoker.addCommand(command2);
    
    // Note: executeMenu() can't be tested directly because it involves user input
    // We can only verify that commands were added successfully
    
    // This test is limited since CommandInvoker::executeMenu() requires console interaction
    // In a real test environment, we would mock the console input
}