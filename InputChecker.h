#ifndef _INPUT_CHECKER_H_
#define _INPUT_CHECKER_H_

#include <string>
#include <vector>
#include <tuple>
#include <cfloat>

using std::string, std::vector, std::tuple, std::make_tuple;

/**
 * @brief Error structure for input validation
 */
struct Error {
    int code;       /**< Error code */
    string message; /**< Error message */
};


/**
 * @brief Class for validating user input
 */
class InputChecker {
public:
    /**
     * @brief Validate integer input
     * @param input The input string to validate
     * @param min Minimum valid value
     * @param max Maximum valid value
     * @return A tuple containing success flag, validated value, and error details if invalid
     */
    static tuple<bool, int, Error> validateInt(string prompt, int promptX, int promptY, int min = INT_MIN, int max = INT_MAX);

    /**
     * @brief Validate floating-point input
     * @param input The input string to validate
     * @param min Minimum valid value
     * @param max Maximum valid value
     * @return A tuple containing success flag, validated value, and error details if invalid
     */
    static tuple<bool, float, Error> validateFloat(string prompt, int promptX, int promptY, float min = -FLT_MAX, float max = FLT_MAX);

    /**
     * @brief Validate string input
     * @param input The input string to validate
     * @param options Optional vector of valid string options
     * @return A tuple containing success flag, validated value, and error details if invalid
     */
    // static tuple<bool, string, Error> validateString(string prompt, vector<string> options = {});
    static tuple<bool, string, Error> validateString(string prompt, int promptX, int promptY);
};

#endif