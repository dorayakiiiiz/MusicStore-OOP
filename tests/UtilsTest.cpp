#include "gtest/gtest.h"
#include "../utils.h"
#include <string>

class UtilsTest : public ::testing::Test {
};

// Test toLower function
TEST_F(UtilsTest, ToLower) {
    // Test with uppercase letters
    EXPECT_EQ("test", toLower("TEST"));
    
    // Test with mixed case
    EXPECT_EQ("test123", toLower("Test123"));
    
    // Test with already lowercase
    EXPECT_EQ("test", toLower("test"));
    
    // Test with empty string
    EXPECT_EQ("", toLower(""));
    
    // Test with special characters
    EXPECT_EQ("test!@#", toLower("TEST!@#"));
}

// Test getMaxOptionsLength function
TEST_F(UtilsTest, GetMaxOptionsLength) {
    std::vector<std::string> options = {"Short", "Medium Length", "A Very Long Option String"};
    
    int maxLength = getMaxOptionsLength(options);
    EXPECT_EQ(25, maxLength); // Length of "A Very Long Option String"
    
    // Test with empty vector
    std::vector<std::string> emptyOptions;
    EXPECT_EQ(0, getMaxOptionsLength(emptyOptions));
    
    // Test with empty strings
    std::vector<std::string> emptyStrings = {"", "", ""};
    EXPECT_EQ(0, getMaxOptionsLength(emptyStrings));
}