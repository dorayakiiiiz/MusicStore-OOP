#include "gtest/gtest.h"
#include "../Order.h"
#include "../Music.h"
#include <vector>

class OrderTest : public ::testing::Test {
protected:
    std::vector<Music> items;
    std::string username;
    float total;

    void SetUp() override {
        username = "testuser";
        
        items.push_back(Music("Song1", "Artist1", "Genre1", 9.99f, 2));
        items.push_back(Music("Song2", "Artist2", "Genre2", 14.99f, 1));
        
        total = 34.97f; // 9.99 * 2 + 14.99 = 34.97
    }
};

// Test constructor và getters
TEST_F(OrderTest, ConstructorAndGetters) {
    Order order(username, items, total);
    
    EXPECT_EQ(username, order.getUsername());
    EXPECT_EQ(total, order.getTotal());
    
    const auto& purchasedItems = order.getPurchasedItems();
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
    std::vector<Music> emptyItems;
    Order order(username, emptyItems, 0.0f);
    
    EXPECT_EQ(username, order.getUsername());
    EXPECT_FLOAT_EQ(0.0f, order.getTotal());
    EXPECT_TRUE(order.getPurchasedItems().empty());
}

// Test với giá trị đặc biệt
TEST_F(OrderTest, SpecialValues) {
    // Order với giá trị âm (not ideal but should handle it)
    Order order(username, items, -1.0f);
    EXPECT_FLOAT_EQ(-1.0f, order.getTotal());
    
    // Order với tên người dùng trống
    Order emptyUserOrder("", items, total);
    EXPECT_EQ("", emptyUserOrder.getUsername());
    EXPECT_FLOAT_EQ(total, emptyUserOrder.getTotal());
}