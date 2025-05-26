#include "gtest/gtest.h"
#include "../InputChecker.h"
#include <tuple>

// Lưu ý: InputChecker rất khó test vì phụ thuộc vào input của người dùng
// Test này chỉ mô phỏng một phần logic của các hàm trong InputChecker

class InputCheckerMock {
public:
    // Mock version of checkInt that doesn't require UI inputs
    static std::tuple<bool, int, Error> checkIntMock(const std::string& input, int min = INT_MIN, int max = INT_MAX) {
        Error error = {0, ""};
        
        // Check if input is empty
        if (input.empty()) {
            error.code = 1;
            error.message = "Input cannot be empty!";
            return std::make_tuple(false, -1, error);
        }
        
        try {
            // Convert string to integer
            int choice = std::stoi(input);
            
            // Check range
            if (choice < min || choice > max) {
                error.code = 2;
                error.message = "Input out of range!";
                return std::make_tuple(false, -1, error);
            }
            return std::make_tuple(true, choice, error);
        } catch (const std::invalid_argument&) {
            // Handle non-numeric input
            error.code = 3;
            error.message = "Invalid input! Please enter a valid number.";
            return std::make_tuple(false, -1, error);
        }
    }
    
    // Mock version of checkFloat that doesn't require UI inputs
    static std::tuple<bool, float, Error> checkFloatMock(const std::string& input, float min = -FLT_MAX, float max = FLT_MAX) {
        Error error = {0, ""};
        
        // Check if input is empty
        if (input.empty()) {
            error.code = 1;
            error.message = "Input cannot be empty!";
            return std::make_tuple(false, -1.0f, error);
        }
        
        try {
            // Convert string to float
            float choice = std::stof(input);
            
            // Check range
            if (choice < min || choice > max) {
                error.code = 2;
                error.message = "Input out of range!";
                return std::make_tuple(false, -1.0f, error);
            }
            return std::make_tuple(true, choice, error);
        } catch (const std::invalid_argument&) {
            // Handle non-numeric input
            error.code = 3;
            error.message = "Invalid input! Please enter a valid number.";
            return std::make_tuple(false, -1.0f, error);
        }
    }
    
    // Mock version of checkString that doesn't require UI inputs
    static std::tuple<bool, std::string, Error> checkStringMock(const std::string& input) {
        Error error = {0, ""};
        
        // Check if input is empty
        if (input.empty()) {
            error.code = 1;
            error.message = "Input cannot be empty!";
            return std::make_tuple(false, "", error);
        }
        return std::make_tuple(true, input, error);
    }
};

class InputCheckerTest : public ::testing::Test {};

// Test checkInt function
TEST_F(InputCheckerTest, CheckIntMock) {
    bool isValid;
    int value;
    Error error;
    
    // Valid input
    std::tie(isValid, value, error) = InputCheckerMock::checkIntMock("123", 0, 200);
    EXPECT_TRUE(isValid);
    EXPECT_EQ(123, value);
    EXPECT_EQ(0, error.code);
    
    // Empty input
    std::tie(isValid, value, error) = InputCheckerMock::checkIntMock("", 0, 200);
    EXPECT_FALSE(isValid);
    EXPECT_EQ(1, error.code);
    
    // Out of range input
    std::tie(isValid, value, error) = InputCheckerMock::checkIntMock("250", 0, 200);
    EXPECT_FALSE(isValid);
    EXPECT_EQ(2, error.code);
    
    // Invalid input (not a number)
    std::tie(isValid, value, error) = InputCheckerMock::checkIntMock("abc", 0, 200);
    EXPECT_FALSE(isValid);
    EXPECT_EQ(3, error.code);
}

// Test checkFloat function
TEST_F(InputCheckerTest, CheckFloatMock) {
    bool isValid;
    float value;
    Error error;
    
    // Valid input
    std::tie(isValid, value, error) = InputCheckerMock::checkFloatMock("12.34", 0.0f, 20.0f);
    EXPECT_TRUE(isValid);
    EXPECT_FLOAT_EQ(12.34f, value);
    EXPECT_EQ(0, error.code);
    
    // Empty input
    std::tie(isValid, value, error) = InputCheckerMock::checkFloatMock("", 0.0f, 20.0f);
    EXPECT_FALSE(isValid);
    EXPECT_EQ(1, error.code);
    
    // Out of range input
    std::tie(isValid, value, error) = InputCheckerMock::checkFloatMock("25.5", 0.0f, 20.0f);
    EXPECT_FALSE(isValid);
    EXPECT_EQ(2, error.code);
    
    // Invalid input (not a number)
    std::tie(isValid, value, error) = InputCheckerMock::checkFloatMock("abc", 0.0f, 20.0f);
    EXPECT_FALSE(isValid);
    EXPECT_EQ(3, error.code);
}

// Test checkString function
TEST_F(InputCheckerTest, CheckStringMock) {
    bool isValid;
    std::string value;
    Error error;
    
    // Valid input
    std::tie(isValid, value, error) = InputCheckerMock::checkStringMock("test string");
    EXPECT_TRUE(isValid);
    EXPECT_EQ("test string", value);
    EXPECT_EQ(0, error.code);
    
    // Empty input
    std::tie(isValid, value, error) = InputCheckerMock::checkStringMock("");
    EXPECT_FALSE(isValid);
    EXPECT_EQ(1, error.code);
}