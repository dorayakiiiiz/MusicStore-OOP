#ifndef MOCK_CONSOLE_H
#define MOCK_CONSOLE_H

#include <string>
#include <vector>
#include <sstream>

// Mock class for testing UI logic without actual console output
class MockConsole {
private:
    std::stringstream outputBuffer;
    std::vector<std::string> inputQueue;
    int currentInput;

public:
    MockConsole() : currentInput(0) {}

    // Simulate input
    void queueInput(const std::string& input) {
        inputQueue.push_back(input);
    }

    // Get next input string
    std::string getInput() {
        if (currentInput < inputQueue.size()) {
            return inputQueue[currentInput++];
        }
        return "";
    }

    // Capture output
    void print(const std::string& text) {
        outputBuffer << text;
    }

    // Capture output with newline
    void println(const std::string& text) {
        outputBuffer << text << "\n";
    }

    // Get all captured output
    std::string getOutput() const {
        return outputBuffer.str();
    }

    // Clear output buffer
    void clearOutput() {
        outputBuffer.str("");
    }

    // Clear input queue
    void clearInput() {
        inputQueue.clear();
        currentInput = 0;
    }
};

#endif // MOCK_CONSOLE_H