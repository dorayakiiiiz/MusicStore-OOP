#include "gtest/gtest.h"
#include "../UserService.h"
#include "MockDao.h"
#include <memory>

// Tạo subclass của UserService cho testing
class TestUserService : public UserService {
public:
    TestUserService(std::shared_ptr<IDataProvider> provider) : UserService(provider) {}
};

class UserServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockDao> mockDao;
    std::shared_ptr<TestUserService> service;
    std::vector<std::shared_ptr<User>> testUsers;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockDao>();
        
        // Test data
        testUsers = {
            std::make_shared<Customer>("customer1", "pass1"),
            std::make_shared<Admin>("admin1", "pass2"),
            std::make_shared<Customer>("customer2", "pass3")
        };
        
        // Set data vào mock dao
        mockDao->setUsers(testUsers);
        
        // Tạo service instance để test
        service = std::make_shared<TestUserService>(mockDao);
    }
};

// Test method getAllUsers
TEST_F(UserServiceTest, GetAllUsers) {
    auto result = service->getAllUsers();
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("customer1", result[0]->getUsername());
    EXPECT_EQ("admin1", result[1]->getUsername());
    EXPECT_EQ("customer2", result[2]->getUsername());
}

// Test method getUserById
TEST_F(UserServiceTest, GetUserById) {
    auto user = service->getUserById(2);
    
    ASSERT_NE(nullptr, user);
    EXPECT_EQ("admin1", user->getUsername());
    EXPECT_EQ(Role::ADMIN, user->getRole());
    
    // Test invalid ID
    auto invalidUser = service->getUserById(10);
    EXPECT_EQ(nullptr, invalidUser);
}

// Test method deleteUserById
TEST_F(UserServiceTest, DeleteUserById) {
    // Delete customer2
    EXPECT_TRUE(service->deleteUserById(3));
    
    auto allUsers = service->getAllUsers();
    ASSERT_EQ(2, allUsers.size());
    EXPECT_EQ("customer1", allUsers[0]->getUsername());
    EXPECT_EQ("admin1", allUsers[1]->getUsername());
    
    // Test delete with invalid ID
    EXPECT_FALSE(service->deleteUserById(10));
    EXPECT_EQ(2, service->getAllUsers().size());
}

// Test method getAllCustomers
TEST_F(UserServiceTest, GetAllCustomers) {
    auto customers = service->getAllCustomers();
    
    ASSERT_EQ(2, customers.size());
    EXPECT_EQ("customer1", customers[0]->getUsername());
    EXPECT_EQ("customer2", customers[1]->getUsername());
    EXPECT_EQ(Role::CUSTOMER, customers[0]->getRole());
    EXPECT_EQ(Role::CUSTOMER, customers[1]->getRole());
}