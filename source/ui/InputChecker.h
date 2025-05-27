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
     * @brief Checking integer input
     * @param input The input string to validate
     * @param min Minimum valid value
     * @param max Maximum valid value
     * @return A tuple containing success flag, validated value, and error details if invalid
     */
    static tuple<bool, int, Error> checkInt(string prompt, int promptX, int promptY, int min = INT_MIN, int max = INT_MAX);

    /**
     * @brief Checking float input
     * @param input The input string to validate
     * @param min Minimum valid value
     * @param max Maximum valid value
     * @return A tuple containing success flag, validated value, and error details if invalid
     */
    static tuple<bool, float, Error> checkFloat(string prompt, int promptX, int promptY, float min = -FLT_MAX, float max = FLT_MAX);

    /**
     * @brief Checking string input
     * @param input The input string to validate
     * @param options Optional vector of valid string options
     * @return A tuple containing success flag, validated value, and error details if invalid
     */
    static tuple<bool, string, Error> checkString(string prompt, int promptX, int promptY);
};

#endif