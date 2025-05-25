#include "gtest/gtest.h"
#include "../DiscountStrategy.h"
#include <memory>

class DiscountStrategyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Không cần thiết lập gì đặc biệt
    }
};

// Test PercentageDiscountStrategy
TEST_F(DiscountStrategyTest, PercentageDiscount) {
    PercentageDiscountStrategy strategy(20); // 20% discount
    
    // Test các method
    EXPECT_EQ("Percentage", strategy.getType());
    EXPECT_EQ(20, strategy.getValue());
    
    // Test calculateDiscount
    EXPECT_FLOAT_EQ(20.0f, strategy.calculateDiscount(100.0f)); // 20% of 100 = 20
    EXPECT_FLOAT_EQ(50.0f, strategy.calculateDiscount(250.0f)); // 20% of 250 = 50
    
    // Test setValue
    strategy.setValue(30);
    EXPECT_EQ(30, strategy.getValue());
    EXPECT_FLOAT_EQ(30.0f, strategy.calculateDiscount(100.0f)); // 30% of 100 = 30
    
    // Test toString
    EXPECT_EQ(" Percentage discount: 30%", strategy.toString());
}

// Test FixedDiscountStrategy
TEST_F(DiscountStrategyTest, FixedDiscount) {
    FixedDiscountStrategy strategy(15); // $15 discount
    
    // Test các method
    EXPECT_EQ("Fixed", strategy.getType());
    EXPECT_EQ(15, strategy.getValue());
    
    // Test calculateDiscount
    EXPECT_FLOAT_EQ(15.0f, strategy.calculateDiscount(100.0f)); // Fixed $15 off
    EXPECT_FLOAT_EQ(10.0f, strategy.calculateDiscount(10.0f));  // Cannot discount more than total
    
    // Test setValue
    strategy.setValue(25);
    EXPECT_EQ(25, strategy.getValue());
    EXPECT_FLOAT_EQ(25.0f, strategy.calculateDiscount(100.0f));
    
    // Test toString
    EXPECT_EQ(" Fixed discount: 25$", strategy.toString());
}

// Test với giá trị đặc biệt
TEST_F(DiscountStrategyTest, EdgeCases) {
    // 0% discount
    PercentageDiscountStrategy zeroPercentage(0);
    EXPECT_FLOAT_EQ(0.0f, zeroPercentage.calculateDiscount(100.0f));
    
    // 100% discount
    PercentageDiscountStrategy fullPercentage(100);
    EXPECT_FLOAT_EQ(100.0f, fullPercentage.calculateDiscount(100.0f));
    
    // $0 discount
    FixedDiscountStrategy zeroFixed(0);
    EXPECT_FLOAT_EQ(0.0f, zeroFixed.calculateDiscount(100.0f));
    
    // Negative value discount (not ideal but should handle it)
    PercentageDiscountStrategy negPercentage(-10);
    EXPECT_FLOAT_EQ(-10.0f, negPercentage.calculateDiscount(100.0f));
    
    FixedDiscountStrategy negFixed(-5);
    EXPECT_FLOAT_EQ(-5.0f, negFixed.calculateDiscount(100.0f));
}