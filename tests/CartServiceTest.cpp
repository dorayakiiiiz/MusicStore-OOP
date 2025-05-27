#include "gtest/gtest.h"
#include "../source/services/CartService.h"
#include "../source/models/Cart.h"
#include "MockSQLDao.h"
#include <memory>

// Tạo subclass của CartService cho testing
class TestCartService : public CartService {
public:
    TestCartService(std::shared_ptr<IDataProvider> provider) : CartService(provider) {}
};

class CartServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSqlDao> mockDao;
    std::shared_ptr<TestCartService> service;
    Cart cart;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockSqlDao>();
        
        // Test data
        std::vector<Music> testItems = {
            Music("Song1", "Artist1", "Pop", 9.99f, 10),
            Music("Song2", "Artist2", "Rock", 14.99f, 5),
            Music("Song3", "Artist3", "Jazz", 19.99f, 3)
        };
        
        // Set data vào mock dao
        mockDao->setMusicItems(testItems);
        
        // Tạo service instance để test
        service = std::make_shared<TestCartService>(mockDao);
    }
};

// Test method addItemToCart
TEST_F(CartServiceTest, AddItemToCart) {
    // Add valid item
    EXPECT_TRUE(service->addItemToCart(cart, 1, 2)); // Add 2 units of Song1
    
    auto cartItems = cart.getItems();
    ASSERT_EQ(1, cartItems.size());
    EXPECT_EQ("Song1", cartItems[0].getName());
    EXPECT_EQ(2, cartItems[0].getQuantity());
    
    // Check repository item quantity was updated
    auto allItems = mockDao->music()->getAll();
    EXPECT_EQ(8, allItems[0].getQuantity()); // 10-2=8
    
    // Add more of the same item
    EXPECT_TRUE(service->addItemToCart(cart, 1, 3)); // Add 3 more units of Song1
    
    cartItems = cart.getItems();
    ASSERT_EQ(1, cartItems.size());
    EXPECT_EQ(5, cartItems[0].getQuantity()); // 2+3=5
    
    // Check repository item quantity was updated again
    allItems = mockDao->music()->getAll();
    EXPECT_EQ(5, allItems[0].getQuantity()); // 8-3=5
    
    // Add different item
    EXPECT_TRUE(service->addItemToCart(cart, 2, 1)); // Add 1 unit of Song2
    
    cartItems = cart.getItems();
    ASSERT_EQ(2, cartItems.size());
    EXPECT_EQ("Song2", cartItems[1].getName());
    EXPECT_EQ(1, cartItems[1].getQuantity());
    
    // Try to add more than available
    EXPECT_FALSE(service->addItemToCart(cart, 3, 5)); // Only 3 units available
}

// Test method removeItemFromCart
TEST_F(CartServiceTest, RemoveItemFromCart) {
    // Setup cart with items
    service->addItemToCart(cart, 1, 2); // Add 2 units of Song1
    service->addItemToCart(cart, 2, 1); // Add 1 unit of Song2
    
    // Initial state
    auto initialItems = mockDao->music()->getAll();
    EXPECT_EQ(8, initialItems[0].getQuantity()); // 10-2=8
    EXPECT_EQ(4, initialItems[1].getQuantity()); // 5-1=4
    
    // Remove item
    EXPECT_TRUE(service->removeItemFromCart(cart, 0)); // Remove Song1
    
    // Verify cart state
    auto cartItems = cart.getItems();
    ASSERT_EQ(1, cartItems.size());
    EXPECT_EQ("Song2", cartItems[0].getName());
    
    // Verify repository state (quantity should be restored)
    auto updatedItems = mockDao->music()->getAll();
    EXPECT_EQ(10, updatedItems[0].getQuantity()); // 8+2=10 (restored)
    
    // Try to remove with invalid index
    EXPECT_FALSE(service->removeItemFromCart(cart, 10));
}