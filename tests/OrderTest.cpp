#include "gtest/gtest.h"
#include "../Order.h"
#include "../Music.h"
#include <vector>

class OrderTest : public ::testing::Test {
protected:
    std::vector<Music> items;
    std::string username;
    float total;
    Order testOrder;
    Order emptyOrder;
    Order defaultOrder;

    void SetUp() override {
        username = "testuser";
        
        items.push_back(Music("Song1", "Artist1", "Genre1", 9.99f, 2));
        items.push_back(Music("Song2", "Artist2", "Genre2", 14.99f, 1));
        
        total = 34.97f; // 9.99 * 2 + 14.99 = 34.97
        testOrder = Order(username, items, total);
        emptyOrder = Order(username, {}, 0.0f);
        defaultOrder = Order(); // Default constructor
    }
};

// Test constructor và getters
TEST_F(OrderTest, ConstructorAndGetters) {
    EXPECT_EQ(username, testOrder.getUsername());
    EXPECT_FLOAT_EQ(total, testOrder.getTotal());
    
    const auto& purchasedItems = testOrder.getPurchasedItems();
    ASSERT_EQ(2, purchasedItems.size());
    
    EXPECT_EQ("Song1", purchasedItems[0].getName());
    EXPECT_EQ("Artist1", purchasedItems[0].getArtist());
    EXPECT_EQ(2, purchasedItems[0].getQuantity());
    
    EXPECT_EQ("Song2", purchasedItems[1].getName());
    EXPECT_EQ("Artist2", purchasedItems[1].getArtist());
    EXPECT_EQ(1, purchasedItems[1].getQuantity());
}

// Test với order trống
TEST_F(OrderTest, EmptyOrder) {
    EXPECT_EQ(username, emptyOrder.getUsername());
    EXPECT_FLOAT_EQ(0.0f, emptyOrder.getTotal());
    EXPECT_TRUE(emptyOrder.getPurchasedItems().empty());
}

// Test default constructor
TEST_F(OrderTest, DefaultConstructor) {
    EXPECT_EQ("", defaultOrder.getUsername());
    EXPECT_FLOAT_EQ(0.0f, defaultOrder.getTotal());
    EXPECT_TRUE(defaultOrder.getPurchasedItems().empty());
}

// Test với giá trị đặc biệt
TEST_F(OrderTest, SpecialValues) {
    // Order với giá trị âm
    Order negativeOrder(username, items, -10.0f);
    EXPECT_FLOAT_EQ(-10.0f, negativeOrder.getTotal());
    
    // Order với username trống
    Order emptyUsernameOrder("", items, total);
    EXPECT_EQ("", emptyUsernameOrder.getUsername());
    EXPECT_FLOAT_EQ(total, emptyUsernameOrder.getTotal());
}
