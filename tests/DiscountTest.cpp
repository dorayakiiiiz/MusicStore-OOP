#include "gtest/gtest.h"
#include "../Discount.h"
#include "../DiscountStrategy.h"
#include <memory>

class DiscountTest : public ::testing::Test {
protected:
    std::shared_ptr<DiscountStrategy> percentageStrategy;
    std::shared_ptr<DiscountStrategy> fixedStrategy;
    std::string username;
    std::string code;

    void SetUp() override {
        username = "testuser";
        code = "ABC123";
        percentageStrategy = std::make_shared<PercentageDiscountStrategy>(20); // 20% discount
        fixedStrategy = std::make_shared<FixedDiscountStrategy>(15);          // $15 fixed discount
    }
};

// Test constructor và getters
TEST_F(DiscountTest, ConstructorAndGetters) {
    Discount percentageDiscount(code, username, percentageStrategy);
    
    EXPECT_EQ(code, percentageDiscount.getCode());
    EXPECT_EQ(username, percentageDiscount.getUsername());
    EXPECT_EQ("Percentage", percentageDiscount.getType());
    EXPECT_EQ(20, percentageDiscount.getValue());
    
    // Test toString
    std::string expected = code + " - " + percentageStrategy->toString();
    EXPECT_EQ(expected, percentageDiscount.toString());
}

// Test apply method
TEST_F(DiscountTest, ApplyDiscount) {
    Discount percentageDiscount(code, username, percentageStrategy);
    Discount fixedDiscount("XYZ789", username, fixedStrategy);
    
    float total = 100.0f;
    
    // Test percentage discount: 100 - 20% = 80
    EXPECT_FLOAT_EQ(80.0f, percentageDiscount.apply(total));
    
    // Test fixed discount: 100 - 15 = 85
    EXPECT_FLOAT_EQ(85.0f, fixedDiscount.apply(total));
    
    // Test discount trên số nhỏ hơn giá trị discount
    EXPECT_FLOAT_EQ(0.0f, fixedDiscount.apply(10.0f)); // 10 - 15 would be negative, return 0 instead
}

// Test với các giá trị đặc biệt
TEST_F(DiscountTest, EdgeCases) {
    // Discount với code trống
    Discount emptyCodeDiscount("", username, percentageStrategy);
    EXPECT_EQ("", emptyCodeDiscount.getCode());
    EXPECT_FLOAT_EQ(80.0f, emptyCodeDiscount.apply(100.0f));
    
    // Discount với username trống
    Discount emptyUsernameDiscount(code, "", percentageStrategy);
    EXPECT_EQ("", emptyUsernameDiscount.getUsername());
    EXPECT_FLOAT_EQ(80.0f, emptyUsernameDiscount.apply(100.0f));
    
    // Discount với giá trị 0
    auto zeroPercentStrategy = std::make_shared<PercentageDiscountStrategy>(0);
    Discount zeroDiscount(code, username, zeroPercentStrategy);
    EXPECT_FLOAT_EQ(100.0f, zeroDiscount.apply(100.0f)); // No discount applied
    
    // Discount với giá trị 100%
    auto fullPercentStrategy = std::make_shared<PercentageDiscountStrategy>(100);
    Discount fullDiscount(code, username, fullPercentStrategy);
    EXPECT_FLOAT_EQ(0.0f, fullDiscount.apply(100.0f)); // Full discount applied
}