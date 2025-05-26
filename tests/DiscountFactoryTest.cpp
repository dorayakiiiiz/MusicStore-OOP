#include "gtest/gtest.h"
#include "../DiscountFactory.h"
#include <memory>

class DiscountFactoryTest : public ::testing::Test {
protected:
    DiscountFactory factory;
};

// Test getStrategy cho các loại discount
TEST_F(DiscountFactoryTest, GetStrategyByType) {
    // Test với PERCENTAGE discount
    auto percentageStrategy = factory.getStrategy(DiscountType::PERCENTAGE);
    ASSERT_NE(nullptr, percentageStrategy);
    EXPECT_EQ("Percentage", percentageStrategy->getType());
    
    // Test với FIXED_AMOUNT discount
    auto fixedStrategy = factory.getStrategy(DiscountType::FIXED_AMOUNT);
    ASSERT_NE(nullptr, fixedStrategy);
    EXPECT_EQ("Fixed", fixedStrategy->getType());
}

// Test initial values
TEST_F(DiscountFactoryTest, InitialValues) {
    // Factories thường tạo object với giá trị mặc định
    auto percentageStrategy = factory.getStrategy(DiscountType::PERCENTAGE);
    EXPECT_EQ(0, percentageStrategy->getValue());
    
    auto fixedStrategy = factory.getStrategy(DiscountType::FIXED_AMOUNT);
    EXPECT_EQ(0, fixedStrategy->getValue());
}

// Test change values
TEST_F(DiscountFactoryTest, ChangeValues) {
    auto percentageStrategy = factory.getStrategy(DiscountType::PERCENTAGE);
    percentageStrategy->setValue(20);
    EXPECT_EQ(20, percentageStrategy->getValue());
    
    auto fixedStrategy = factory.getStrategy(DiscountType::FIXED_AMOUNT);
    fixedStrategy->setValue(15);
    EXPECT_EQ(15, fixedStrategy->getValue());
}

// Test calculate với các giá trị mới
TEST_F(DiscountFactoryTest, CalculateWithNewValues) {
    auto percentageStrategy = factory.getStrategy(DiscountType::PERCENTAGE);
    percentageStrategy->setValue(20);
    EXPECT_FLOAT_EQ(20.0f, percentageStrategy->calculateDiscount(100.0f));
    
    auto fixedStrategy = factory.getStrategy(DiscountType::FIXED_AMOUNT);
    fixedStrategy->setValue(15);
    EXPECT_FLOAT_EQ(15.0f, fixedStrategy->calculateDiscount(100.0f));
}

// Test invalid discount type
TEST_F(DiscountFactoryTest, InvalidDiscountType) {
    // Tạo một DiscountType không hợp lệ
    DiscountType invalidType = static_cast<DiscountType>(999);
    auto invalidStrategy = factory.getStrategy(invalidType);
    
    // Expected: nullptr
    EXPECT_EQ(nullptr, invalidStrategy);
}