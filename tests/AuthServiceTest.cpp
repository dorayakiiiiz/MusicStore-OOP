#include "gtest/gtest.h"
#include "../AuthService.h"
#include "MockDao.h"
#include <memory>

// Tạo subclass của AuthService cho testing
class TestAuthService : public AuthService {
public:
    TestAuthService(std::shared_ptr<IDataProvider> provider) : AuthService(provider) {}
};

class AuthServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockDao> mockDao;
    std::shared_ptr<TestAuthService> service;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockDao>();
        
        // Test data
        std::vector<std::shared_ptr<User>> testUsers = {
            std::make_shared<Customer>("customer1", "pass1"),
            std::make_shared<Admin>("admin1", "pass2")
        };
        
        // Set data vào mock dao
        mockDao->setUsers(testUsers);
        
        // Tạo service instance để test
        service = std::make_shared<TestAuthService>(mockDao);
    }
};

// Test method registerUser
TEST_F(AuthServiceTest, RegisterUser) {
    // Register new customer
    EXPECT_TRUE(service->registerUser("newcustomer", "newpass", Role::CUSTOMER));
    
    // Register new admin
    EXPECT_TRUE(service->registerUser("newadmin", "adminpass", Role::ADMIN));
    
    // Try to register with existing username
    EXPECT_FALSE(service->registerUser("customer1", "anotherpass", Role::CUSTOMER));
    
    // Verify that users were added
    auto allUsers = mockDao->user()->getAll();
    ASSERT_EQ(4, allUsers.size());
    
    // Verify new customer
    EXPECT_EQ("newcustomer", allUsers[2]->getUsername());
    EXPECT_EQ("newpass", allUsers[2]->getPassword());
    EXPECT_EQ(Role::CUSTOMER, allUsers[2]->getRole());
    
    // Verify new admin
    EXPECT_EQ("newadmin", allUsers[3]->getUsername());
    EXPECT_EQ("adminpass", allUsers[3]->getPassword());
    EXPECT_EQ(Role::ADMIN, allUsers[3]->getRole());
}

// Test method loginUser
TEST_F(AuthServiceTest, LoginUser) {
    // Login with valid credentials (customer)
    auto customer = service->loginUser("customer1", "pass1");
    ASSERT_NE(nullptr, customer);
    EXPECT_EQ("customer1", customer->getUsername());
    EXPECT_EQ(Role::CUSTOMER, customer->getRole());
    
    // Login with valid credentials (admin)
    auto admin = service->loginUser("admin1", "pass2");
    ASSERT_NE(nullptr, admin);
    EXPECT_EQ("admin1", admin->getUsername());
    EXPECT_EQ(Role::ADMIN, admin->getRole());
    
    // Login with invalid username
    auto invalidUser = service->loginUser("nonexistent", "pass");
    EXPECT_EQ(nullptr, invalidUser);
    
    // Login with invalid password
    auto invalidPass = service->loginUser("customer1", "wrongpass");
    EXPECT_EQ(nullptr, invalidPass);
}