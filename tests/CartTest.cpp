#include "gtest/gtest.h"
#include "../Cart.h"
#include "../Music.h"

class CartTest : public ::testing::Test {
protected:
    Cart cart;
    Music testMusic1;
    Music testMusic2;

    void SetUp() override {
        testMusic1 = Music("Song1", "Artist1", "Genre1", 9.99f, 5);
        testMusic2 = Music("Song2", "Artist2", "Genre2", 14.99f, 3);
    }
};

// Test thêm item vào cart
TEST_F(CartTest, AddItems) {
    // Thêm item đầu tiên vào cart
    cart.addItems(testMusic1, 2);
    
    auto items = cart.getItems();
    ASSERT_EQ(1, items.size());
    EXPECT_EQ("Song1", items[0].getName());
    EXPECT_EQ(2, items[0].getQuantity());
    
    // Thêm thêm lượng item đầu tiên
    cart.addItems(testMusic1, 3);
    items = cart.getItems();
    ASSERT_EQ(1, items.size());
    EXPECT_EQ(5, items[0].getQuantity()); // 2 + 3 = 5
    
    // Thêm item thứ hai
    cart.addItems(testMusic2, 1);
    items = cart.getItems();
    ASSERT_EQ(2, items.size());
    EXPECT_EQ("Song2", items[1].getName());
    EXPECT_EQ(1, items[1].getQuantity());
}

// Test xóa item khỏi cart
TEST_F(CartTest, RemoveItem) {
    cart.addItems(testMusic1, 2);
    cart.addItems(testMusic2, 3);
    
    // Xóa item đầu tiên
    cart.removeItem(0);
    
    auto items = cart.getItems();
    ASSERT_EQ(1, items.size());
    EXPECT_EQ("Song2", items[0].getName());
    
    // Xóa item không tồn tại (index ngoài range)
    cart.removeItem(5); // Không có exception, chỉ có early return
    items = cart.getItems();
    EXPECT_EQ(1, items.size()); // Số lượng item không đổi
}

// Test tính toán tổng giá trị
TEST_F(CartTest, CalculateTotal) {
    cart.addItems(testMusic1, 2); // 2 * 9.99 = 19.98
    cart.addItems(testMusic2, 3); // 3 * 14.99 = 44.97
    
    float total = cart.calculateTotal();
    EXPECT_FLOAT_EQ(19.98f + 44.97f, total);
}

// Test xóa toàn bộ cart
TEST_F(CartTest, Clear) {
    cart.addItems(testMusic1, 2);
    cart.addItems(testMusic2, 3);
    
    cart.clear();
    auto items = cart.getItems();
    EXPECT_TRUE(items.empty());
}

// Test trường hợp đặc biệt
TEST_F(CartTest, SpecialCases) {
    // Thêm item với số lượng 0
    cart.addItems(testMusic1, 0);
    auto items = cart.getItems();
    ASSERT_EQ(1, items.size());
    EXPECT_EQ(0, items[0].getQuantity());
    
    // Thêm item với số lượng âm
    cart.clear();
    cart.addItems(testMusic1, -1);
    items = cart.getItems();
    ASSERT_EQ(1, items.size());
    EXPECT_EQ(-1, items[0].getQuantity());
}