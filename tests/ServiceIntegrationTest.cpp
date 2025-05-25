#include "gtest/gtest.h"
#include "../MusicService.h"
#include "../UserService.h"
#include "../OrderService.h"
#include "../CartService.h"
#include "../AuthService.h"
#include "../DiscountService.h"
#include "../SalesRecordService.h"
#include "MockDao.h"
#include <memory>

class ServiceIntegrationTest : public ::testing::Test {
protected:
    std::shared_ptr<MockDao> mockDao;
    
    void SetUp() override {
        mockDao = std::make_shared<MockDao>();
        
        // Set up test data in mock DAO
        std::vector<Music> musicItems = {
            Music("Song1", "Artist1", "Pop", 9.99f, 10),
            Music("Song2", "Artist2", "Rock", 14.99f, 5)
        };
        mockDao->setMusicItems(musicItems);
        
        std::vector<std::shared_ptr<User>> users = {
            std::make_shared<Customer>("customer1", "pass1"),
            std::make_shared<Admin>("admin1", "pass2")
        };
        mockDao->setUsers(users);
        
        // Reset all service instances to use our mock DAO
        MusicService::getInstance(mockDao);
        UserService::getInstance(mockDao);
        OrderService::getInstance(mockDao);
        CartService::getInstance(mockDao);
        AuthService::getInstance(mockDao);
        DiscountService::getInstance(mockDao);
        SalesRecordService::getInstance(mockDao);
    }
};

// Test integrated purchase workflow
TEST_F(ServiceIntegrationTest, PurchaseWorkflow) {
    // 1. User logs in
    auto user = AuthService::getInstance()->loginUser("customer1", "pass1");
    ASSERT_NE(nullptr, user);
    EXPECT_EQ("customer1", user->getUsername());
    
    // 2. Create a cart
    Cart cart;
    
    // 3. Add items to cart
    bool added = CartService::getInstance()->addItemToCart(cart, 1, 2); // Add 2 of Song1
    EXPECT_TRUE(added);
    
    added = CartService::getInstance()->addItemToCart(cart, 2, 1); // Add 1 of Song2
    EXPECT_TRUE(added);
    
    // 4. Check cart content
    auto cartItems = cart.getItems();
    ASSERT_EQ(2, cartItems.size());
    EXPECT_EQ("Song1", cartItems[0].getName());
    EXPECT_EQ(2, cartItems[0].getQuantity());
    EXPECT_EQ("Song2", cartItems[1].getName());
    EXPECT_EQ(1, cartItems[1].getQuantity());
    
    // 5. Calculate cart total
    float total = cart.calculateTotal();
    EXPECT_FLOAT_EQ((9.99f * 2) + 14.99f, total);
    
    // 6. Checkout
    OrderService::getInstance()->checkout(user->getUsername(), cart, total);
    
    // 7. Verify cart is empty after checkout
    EXPECT_TRUE(cart.getItems().empty());
    
    // 8. Verify order was created
    auto orders = OrderService::getInstance()->getUserOrders(user->getUsername());
    ASSERT_EQ(1, orders.size());
    EXPECT_EQ("customer1", orders[0].getUsername());
    EXPECT_FLOAT_EQ(total, orders[0].getTotal());
    
    auto purchasedItems = orders[0].getPurchasedItems();
    ASSERT_EQ(2, purchasedItems.size());
    EXPECT_EQ("Song1", purchasedItems[0].getName());
    EXPECT_EQ(2, purchasedItems[0].getQuantity());
    EXPECT_EQ("Song2", purchasedItems[1].getName());
    EXPECT_EQ(1, purchasedItems[1].getQuantity());
}

// Test workflow with discount applied
TEST_F(ServiceIntegrationTest, DiscountWorkflow) {
    // Set up a discount
    auto percentageStrategy = std::make_shared<PercentageDiscountStrategy>(20); // 20% off
    auto discount = std::make_shared<Discount>("TEST20", "customer1", percentageStrategy);
    
    std::vector<std::shared_ptr<Discount>> discounts = { discount };
    mockDao->setDiscounts(discounts);
    
    // Create a cart and add items
    Cart cart;
    CartService::getInstance()->addItemToCart(cart, 1, 1); // Add Song1
    
    float total = cart.calculateTotal(); // 9.99
    
    // Apply the discount
    float discountedTotal = DiscountService::getInstance()->applyDiscount(discount, total);
    
    // Verify discounted amount (20% off)
    EXPECT_FLOAT_EQ(total * 0.8f, discountedTotal);
}