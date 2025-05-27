#include "gtest/gtest.h"
#include "../source/models/Discount.h"
#include "../source/strategies/DiscountStrategy.h"
#include <memory>

class DiscountTest : public ::testing::Test {
protected:
    std::shared_ptr<DiscountStrategy> percentageStrategy;
    std::shared_ptr<DiscountStrategy> fixedStrategy;
    std::string code;
    std::string username;
    std::shared_ptr<Discount> percentageDiscount;
    std::shared_ptr<Discount> fixedDiscount;

    void SetUp() override {
        code = "TEST123";
        username = "testuser";
        percentageStrategy = std::make_shared<PercentageDiscountStrategy>(20); // 20% discount
        fixedStrategy = std::make_shared<FixedDiscountStrategy>(15);          // $15 fixed discount
        
        percentageDiscount = std::make_shared<Discount>(code, username, percentageStrategy);
        fixedDiscount = std::make_shared<Discount>("FIXED", username, fixedStrategy);
    }
};

// Test PercentageDiscountStrategy
TEST_F(DiscountTest, PercentageStrategyCalculation) {
    // 20% off $100 = $20 discount
    EXPECT_FLOAT_EQ(20.0f, percentageStrategy->calculateDiscount(100.0f));
    
    // 20% off $50 = $10 discount
    EXPECT_FLOAT_EQ(10.0f, percentageStrategy->calculateDiscount(50.0f));
    
    // 20% off $0 = $0 discount
    EXPECT_FLOAT_EQ(0.0f, percentageStrategy->calculateDiscount(0.0f));
    
    // 20% off negative value - should return negative discount
    EXPECT_FLOAT_EQ(-2.0f, percentageStrategy->calculateDiscount(-10.0f));
}

// Test FixedDiscountStrategy
TEST_F(DiscountTest, FixedStrategyCalculation) {
    // $15 off $100 = $15 discount
    EXPECT_FLOAT_EQ(15.0f, fixedStrategy->calculateDiscount(100.0f));
    
    // $15 off $10 = $10 discount (shouldn't exceed total)
    EXPECT_FLOAT_EQ(10.0f, fixedStrategy->calculateDiscount(10.0f));
    
    // $15 off $0 = $0 discount
    EXPECT_FLOAT_EQ(0.0f, fixedStrategy->calculateDiscount(0.0f));
    
    // $15 off negative value - should return negative amount
    EXPECT_FLOAT_EQ(-10.0f, fixedStrategy->calculateDiscount(-10.0f));
}

// Test DiscountStrategy getters và setters
TEST_F(DiscountTest, StrategyGettersAndSetters) {
    EXPECT_EQ("Percentage", percentageStrategy->getType());
    EXPECT_EQ(20, percentageStrategy->getValue());
    
    EXPECT_EQ("Fixed", fixedStrategy->getType());
    EXPECT_EQ(15, fixedStrategy->getValue());
    
    // Test setValue
    percentageStrategy->setValue(30);
    EXPECT_EQ(30, percentageStrategy->getValue());
    EXPECT_FLOAT_EQ(30.0f, percentageStrategy->calculateDiscount(100.0f));
    
    fixedStrategy->setValue(25);
    EXPECT_EQ(25, fixedStrategy->getValue());
    EXPECT_FLOAT_EQ(25.0f, fixedStrategy->calculateDiscount(100.0f));
}

// Test Strategy toString methods
TEST_F(DiscountTest, StrategyToString) {
    EXPECT_EQ(" Percentage discount: 20%", percentageStrategy->toString());
    EXPECT_EQ(" Fixed discount: 15$", fixedStrategy->toString());
    
    percentageStrategy->setValue(30);
    fixedStrategy->setValue(25);
    
    EXPECT_EQ(" Percentage discount: 30%", percentageStrategy->toString());
    EXPECT_EQ(" Fixed discount: 25$", fixedStrategy->toString());
}

// Test Discount constructor và getters
TEST_F(DiscountTest, DiscountConstructorAndGetters) {
    EXPECT_EQ(code, percentageDiscount->getCode());
    EXPECT_EQ(username, percentageDiscount->getUsername());
    EXPECT_EQ("Percentage", percentageDiscount->getType());
    EXPECT_EQ(20, percentageDiscount->getValue());
}

// Test Discount apply method
TEST_F(DiscountTest, DiscountApply) {
    // Apply percentage discount (20% off)
    EXPECT_FLOAT_EQ(80.0f, percentageDiscount->apply(100.0f)); // 100 - 20% = 80
    EXPECT_FLOAT_EQ(40.0f, percentageDiscount->apply(50.0f));  // 50 - 20% = 40
    
    // Apply fixed discount ($15 off)
    EXPECT_FLOAT_EQ(85.0f, fixedDiscount->apply(100.0f)); // 100 - 15 = 85
    EXPECT_FLOAT_EQ(35.0f, fixedDiscount->apply(50.0f));  // 50 - 15 = 35
    EXPECT_FLOAT_EQ(0.0f, fixedDiscount->apply(10.0f));   // 10 - 15 = -5, should be 0
}

// Test Discount toString method
TEST_F(DiscountTest, DiscountToString) {
    std::string expected = code + " - " + percentageStrategy->toString();
    EXPECT_EQ(expected, percentageDiscount->toString());
}

// Test Discount với giá trị đặc biệt
TEST_F(DiscountTest, DiscountSpecialCases) {
    // Discount với code trống
    auto emptyCodeDiscount = std::make_shared<Discount>("", username, percentageStrategy);
    EXPECT_EQ("", emptyCodeDiscount->getCode());
    
    // Discount với username trống
    auto emptyUsernameDiscount = std::make_shared<Discount>(code, "", percentageStrategy);
    EXPECT_EQ("", emptyUsernameDiscount->getUsername());
    
    // 0% discount
    auto zeroPercentStrategy = std::make_shared<PercentageDiscountStrategy>(0);
    auto zeroPercentDiscount = std::make_shared<Discount>(code, username, zeroPercentStrategy);
    EXPECT_FLOAT_EQ(100.0f, zeroPercentDiscount->apply(100.0f));
    
    // 100% discount
    auto fullPercentStrategy = std::make_shared<PercentageDiscountStrategy>(100);
    auto fullPercentDiscount = std::make_shared<Discount>(code, username, fullPercentStrategy);
    EXPECT_FLOAT_EQ(0.0f, fullPercentDiscount->apply(100.0f));
    
    // $0 discount
    auto zeroFixedStrategy = std::make_shared<FixedDiscountStrategy>(0);
    auto zeroFixedDiscount = std::make_shared<Discount>(code, username, zeroFixedStrategy);
    EXPECT_FLOAT_EQ(100.0f, zeroFixedDiscount->apply(100.0f));
    
    // Negative amount discount
    auto negFixedStrategy = std::make_shared<FixedDiscountStrategy>(-10);
    auto negFixedDiscount = std::make_shared<Discount>(code, username, negFixedStrategy);
    EXPECT_FLOAT_EQ(110.0f, negFixedDiscount->apply(100.0f)); // 100 - (-10) = 110
}