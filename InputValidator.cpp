#include "InputValidator.h"
#include "utils.h"

// get a valid int input from user
tuple <bool, int, Error> InputValidator::validateInt(string prompt, int min, int max) {
    Error error = {0, ""};
    string input = getInput(prompt);
    // Check if input is empty
    if (input.empty()) {
        error.code = 1;
        error.message = "Input cannot be empty!";
        return make_tuple(false, -1, error);
    }
    try {
        // Convert string to integer
        int choice = stoi(input);
        // Validate range
        if (choice < min || choice > max) {
            error.code = 2;
            error.message = "Input out of range!";
            return make_tuple(false, -1, error);
        }
        return make_tuple(true, choice, error);
    } catch (const std::invalid_argument&) {
        // Handle non-numeric input
        error.code = 3;
        error.message = "Invalid input! Please enter a valid number.";
        return make_tuple(false, -1, error);
    }
}

// get a valid float input from user
tuple <bool, float, Error> InputValidator::validateFloat(string prompt, float min, float max) {
    Error error = {0, ""};
    string input = getInput(prompt);
    // Check if input is empty
    if (input.empty()) {
        error.code = 1;
        error.message = "Input cannot be empty!";
        return make_tuple(false, -1.0f, error);
    }
    try {
        // Convert string to float
        float choice = stof(input);
        // Validate range
        if (choice < min || choice > max) {
            error.code = 2;
            error.message = "Input out of range!";
            return make_tuple(false, -1.0f, error);
        }
        return make_tuple(true, choice, error);
    } catch (const std::invalid_argument&) {
        // Handle non-numeric input
        error.code = 3;
        error.message = "Invalid input! Please enter a valid number.";
        return make_tuple(false, -1.0f, error);
    }
}

// get a valid string input from user
tuple <bool, string, Error> InputValidator::validateString(string prompt) {
    Error error = {0, ""};
    string input = getInput(prompt);
    // Check if input is empty
    if (input.empty()) {
        error.code = 1;
        error.message = "Input cannot be empty!";
        return make_tuple(false, "", error);
    }
    // If options are provided, validate that input matches one of them
    // if (option.size() > 0) {
    //     for (const auto& opt : option) {
    //         if (input == opt) {
    //             return make_tuple(true, input, error);
    //         }
    //     }
    //     error.code = 2;
    //     error.message = "Invalid option! Please try again.";
    //     return make_tuple(false, "", error);
    // }
    return make_tuple(true, input, error);
}
