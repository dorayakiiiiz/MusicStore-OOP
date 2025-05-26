#include "gtest/gtest.h"
#include "../DiscountService.h"
#include "MockSQLDao.h"
#include <memory>

// Tạo subclass của DiscountService cho testing
class TestDiscountService : public DiscountService {
public:
    TestDiscountService(std::shared_ptr<IDataProvider> provider) : DiscountService(provider) {};
    
    // Make generateRandomCode return a predictable value for testing
    std::string generateRandomCode() override {
        static int counter = 0;
        return "TEST" + std::to_string(++counter);
    }
};

class DiscountServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSqlDao> mockDao;
    std::shared_ptr<TestDiscountService> service;
    std::vector<std::shared_ptr<Discount>> testDiscounts;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockSqlDao>();
        
        // Create test data
        auto percentageStrategy = std::make_shared<PercentageDiscountStrategy>(20);
        auto fixedStrategy = std::make_shared<FixedDiscountStrategy>(15);
        
        testDiscounts = {
            std::make_shared<Discount>("CODE1", "user1", percentageStrategy),
            std::make_shared<Discount>("CODE2", "user2", fixedStrategy),
            std::make_shared<Discount>("CODE3", "user1", fixedStrategy)
        };
        
        // Set data vào mock dao
        mockDao->setDiscounts(testDiscounts);
        
        // Tạo service instance để test
        service = std::make_shared<TestDiscountService>(mockDao);
    }
};

// Test method getAllDiscounts
TEST_F(DiscountServiceTest, GetAllDiscounts) {
    auto result = service->getAllDiscounts();
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("CODE1", result[0]->getCode());
    EXPECT_EQ("CODE2", result[1]->getCode());
    EXPECT_EQ("CODE3", result[2]->getCode());
}

// Test method applyDiscount
TEST_F(DiscountServiceTest, ApplyDiscount) {
    auto percentageDiscount = testDiscounts[0]; // 20% discount
    auto fixedDiscount = testDiscounts[1]; // $15 discount
    
    // Apply percentage discount
    float total1 = 100.0f;
    float discounted1 = service->applyDiscount(percentageDiscount, total1);
    EXPECT_FLOAT_EQ(80.0f, discounted1); // 100 - 20% = 80
    
    // Apply fixed discount
    float total2 = 50.0f;
    float discounted2 = service->applyDiscount(fixedDiscount, total2);
    EXPECT_FLOAT_EQ(35.0f, discounted2); // 50 - $15 = 35
    
    // Apply fixed discount to small amount
    float total3 = 10.0f;
    float discounted3 = service->applyDiscount(fixedDiscount, total3);
    EXPECT_FLOAT_EQ(0.0f, discounted3); // Should be capped at 0
}

// Test method isValidDiscount
TEST_F(DiscountServiceTest, IsValidDiscount) {
    // Test existing discount
    EXPECT_TRUE(service->isValidDiscount(testDiscounts, testDiscounts[0]));
    
    // Test non-existing discount
    auto newPercentageStrategy = std::make_shared<PercentageDiscountStrategy>(10);
    auto newDiscount = std::make_shared<Discount>("NEWCODE", "user3", newPercentageStrategy);
    EXPECT_FALSE(service->isValidDiscount(testDiscounts, newDiscount));
}

// Test method loadValidDiscounts
TEST_F(DiscountServiceTest, LoadValidDiscounts) {
    // Get discounts for user1
    auto user1Discounts = service->loadValidDiscounts(testDiscounts, "user1");
    ASSERT_EQ(2, user1Discounts.size());
    EXPECT_EQ("CODE1", user1Discounts[0]->getCode());
    EXPECT_EQ("CODE3", user1Discounts[1]->getCode());
    
    // Get discounts for user2
    auto user2Discounts = service->loadValidDiscounts(testDiscounts, "user2");
    ASSERT_EQ(1, user2Discounts.size());
    EXPECT_EQ("CODE2", user2Discounts[0]->getCode());
    
    // Get discounts for non-existing user
    auto user3Discounts = service->loadValidDiscounts(testDiscounts, "user3");
    EXPECT_TRUE(user3Discounts.empty());
}

// Test method removeDiscount
TEST_F(DiscountServiceTest, RemoveDiscount) {
    // Remove first discount
    service->removeDiscount(testDiscounts[0]);
    
    auto remainingDiscounts = service->getAllDiscounts();
    ASSERT_EQ(2, remainingDiscounts.size());
    EXPECT_EQ("CODE2", remainingDiscounts[0]->getCode());
    EXPECT_EQ("CODE3", remainingDiscounts[1]->getCode());
}

// Test method createDiscount
TEST_F(DiscountServiceTest, CreateDiscount) {
    // Create percentage discount
    auto newDiscount = service->createDiscount("user3", DiscountType::PERCENTAGE, 30);
    
    EXPECT_EQ("TEST1", newDiscount->getCode());
    EXPECT_EQ("user3", newDiscount->getUsername());
    EXPECT_EQ("Percentage", newDiscount->getType());
    EXPECT_EQ(30, newDiscount->getValue());
    
    // Verify discount was added to repository
    auto allDiscounts = service->getAllDiscounts();
    ASSERT_EQ(4, allDiscounts.size());
    EXPECT_EQ("TEST1", allDiscounts[3]->getCode());
}