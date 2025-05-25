#include "gtest/gtest.h"
#include "../DiscountFactory.h"
#include "../DiscountStrategy.h"
#include <memory>

class DiscountFactoryTest : public ::testing::Test {
protected:
    DiscountFactory factory;

    void SetUp() override {
        // Factory được khởi tạo mặc định trong constructor
    }
};

// Test tạo các chiến lược giảm giá
TEST_F(DiscountFactoryTest, GetStrategy) {
    // Tạo percentage strategy
    auto percentageStrategy = factory.getStrategy(DiscountType::PERCENTAGE);
    ASSERT_NE(nullptr, percentageStrategy);
    EXPECT_EQ("Percentage", percentageStrategy->getType());
    
    // Tạo fixed strategy
    auto fixedStrategy = factory.getStrategy(DiscountType::FIXED_AMOUNT);
    ASSERT_NE(nullptr, fixedStrategy);
    EXPECT_EQ("Fixed", fixedStrategy->getType());
    
    // Kiểm tra các strategy có hoạt động đúng không
    percentageStrategy->setValue(20); // 20% discount
    fixedStrategy->setValue(15);      // $15 discount
    
    EXPECT_FLOAT_EQ(20.0f, percentageStrategy->calculateDiscount(100.0f)); // 20% of 100 = 20
    EXPECT_FLOAT_EQ(15.0f, fixedStrategy->calculateDiscount(100.0f));      // $15 off 100 = 85
}

// Test với discount type không hợp lệ
TEST_F(DiscountFactoryTest, InvalidDiscountType) {
    // Thử tạo strategy với giá trị không hợp lệ (cast enum)
    auto invalidStrategy = factory.getStrategy(static_cast<DiscountType>(999));
    EXPECT_EQ(nullptr, invalidStrategy);
}