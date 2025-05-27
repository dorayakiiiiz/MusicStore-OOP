#include "gtest/gtest.h"
#include "../source/services/OrderService.h"
#include "../source/models/Cart.h"
#include "MockSQLDao.h"
#include <memory>

// Tạo subclass của OrderService cho testing
class TestOrderService : public OrderService {
public:
    TestOrderService(std::shared_ptr<IDataProvider> provider) : OrderService(provider) {}
};

class OrderServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSqlDao> mockDao;
    std::shared_ptr<TestOrderService> service;
    std::vector<Order> testOrders;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockSqlDao>();
        
        // Test data
        std::vector<Music> items1 = {
            Music("Song1", "Artist1", "Pop", 9.99f, 2),
            Music("Song2", "Artist2", "Rock", 14.99f, 1)
        };
        
        std::vector<Music> items2 = {
            Music("Song3", "Artist3", "Jazz", 19.99f, 1)
        };
        
        testOrders = {
            Order("user1", items1, 34.97f), // 9.99*2 + 14.99 = 34.97
            Order("user2", items2, 19.99f),
            Order("user1", {}, 0.0f)
        };
        
        // Set data vào mock dao
        mockDao->setOrders(testOrders);
        
        // Tạo service instance để test
        service = std::make_shared<TestOrderService>(mockDao);
    }
};

// Test method getAllOrders
TEST_F(OrderServiceTest, GetAllOrders) {
    auto result = service->getAllOrders();
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("user1", result[0].getUsername());
    EXPECT_EQ("user2", result[1].getUsername());
    EXPECT_EQ("user1", result[2].getUsername());
    
    EXPECT_FLOAT_EQ(34.97f, result[0].getTotal());
    EXPECT_FLOAT_EQ(19.99f, result[1].getTotal());
    EXPECT_FLOAT_EQ(0.0f, result[2].getTotal());
}

// Test method checkout
TEST_F(OrderServiceTest, Checkout) {
    Cart cart;
    Music item1("New Song", "New Artist", "Pop", 10.50f, 3);
    Music item2("Another Song", "Another Artist", "Rock", 15.75f, 1);
    
    cart.addItems(item1, 3);
    cart.addItems(item2, 1);
    
    service->checkout("testuser", cart, 47.25f); // 10.50*3 + 15.75 = 47.25
    
    // Verify the order was added
    auto orders = service->getAllOrders();
    ASSERT_EQ(4, orders.size());
    
    auto lastOrder = orders[3];
    EXPECT_EQ("testuser", lastOrder.getUsername());
    EXPECT_FLOAT_EQ(47.25f, lastOrder.getTotal());
    
    // Verify that cart was cleared
    EXPECT_TRUE(cart.getItems().empty());
}

// Test method deleteOrder
TEST_F(OrderServiceTest, DeleteOrder) {
    // Delete all orders for user1
    service->deleteOrder("user1");
    
    auto orders = service->getAllOrders();
    ASSERT_EQ(1, orders.size());
    EXPECT_EQ("user2", orders[0].getUsername());
}

// Test method getUserOrders
TEST_F(OrderServiceTest, GetUserOrders) {
    auto user1Orders = service->getUserOrders("user1");
    ASSERT_EQ(2, user1Orders.size());
    
    auto user2Orders = service->getUserOrders("user2");
    ASSERT_EQ(1, user2Orders.size());
    
    auto nonExistingUserOrders = service->getUserOrders("nonexistent");
    EXPECT_TRUE(nonExistingUserOrders.empty());
}