#include "InputChecker.h"
#include "utils.h"

// get a valid int input from user
tuple <bool, int, Error> InputChecker::checkInt(string prompt, int promptX, int promptY, int min, int max) {
    Error error = {0, ""};
    string input = getInput(prompt, promptX, promptY);
    // Check if input is empty
    if (input.empty()) {
        error.code = 1;
        error.message = "INPUT CANNOT BE EMPTY!";
        return make_tuple(false, -1, error);
    }
    try {
        // Convert string to integer
        int choice = stoi(input);
        // check range
        if (choice < min || choice > max) {
            error.code = 2;
            error.message = "INPUT OUT OF RANGE!";
            return make_tuple(false, -1, error);
        }
        return make_tuple(true, choice, error);
    } catch (const std::invalid_argument&) {
        // Handle non-numeric input
        error.code = 3;
        error.message = "INVALID INPUT! PLEASE ENTER A VALID NUMBER.";
        return make_tuple(false, -1, error);
    }
}

// get a valid float input from user
tuple <bool, float, Error> InputChecker::checkFloat(string prompt, int promptX, int promptY, float min, float max) {
    Error error = {0, ""};
    string input = getInput(prompt, promptX, promptY);
    // Check if input is empty
    if (input.empty()) {
        error.code = 1;
        error.message = "INPUT CANNOT BE EMPTY!";
        return make_tuple(false, -1.0f, error);
    }
    try {
        // Convert string to float
        float choice = stof(input);
        // check range
        if (choice < min || choice > max) {
            error.code = 2;
            error.message = "INPUT OUT OF RANGE!";
            return make_tuple(false, -1.0f, error);
        }
        return make_tuple(true, choice, error);
    } catch (const std::invalid_argument&) {
        // Handle non-numeric input
        error.code = 3;
        error.message = "INVALID INPUT! PLEASE ENTER A VALID NUMBER.";
        return make_tuple(false, -1.0f, error);
    }
}

// get a valid string input from user
tuple <bool, string, Error> InputChecker::checkString(string prompt, int promptX, int promptY) {
    Error error = {0, ""};
    string input = getInput(prompt, promptX, promptY);
    // Check if input is empty
    if (input.empty()) {
        error.code = 1;
        error.message = "INPUT CANNOT BE EMPTY!";
        return make_tuple(false, "", error);
    }
    return make_tuple(true, input, error);
}