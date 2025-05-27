#include "gtest/gtest.h"
#include "../source/services/AuthService.h"
#include "MockSQLDao.h"
#include <memory>

// Tạo subclass của AuthService cho testing
class TestAuthService : public AuthService {
public:
    TestAuthService(std::shared_ptr<IDataProvider> provider) : AuthService(provider) {}
};

class AuthServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSqlDao> mockDao;
    std::shared_ptr<TestAuthService> service;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockSqlDao>();
        
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
    // Đăng ký customer mới
    EXPECT_TRUE(service->registerUser("newcustomer", "newpass", Role::CUSTOMER));
    
    // Đăng ký admin mới
    EXPECT_TRUE(service->registerUser("newadmin", "adminpass", Role::ADMIN));
    
    // Đăng ký username đã tồn tại
    EXPECT_FALSE(service->registerUser("customer1", "anotherpass", Role::CUSTOMER));
    
    // Kiểm tra users đã được thêm vào
    auto allUsers = mockDao->user()->getAll();
    ASSERT_EQ(4, allUsers.size());
    
    // Kiểm tra thông tin customer mới
    EXPECT_EQ("newcustomer", allUsers[2]->getUsername());
    EXPECT_EQ("newpass", allUsers[2]->getPassword());
    EXPECT_EQ(Role::CUSTOMER, allUsers[2]->getRole());
    
    // Kiểm tra thông tin admin mới
    EXPECT_EQ("newadmin", allUsers[3]->getUsername());
    EXPECT_EQ("adminpass", allUsers[3]->getPassword());
    EXPECT_EQ(Role::ADMIN, allUsers[3]->getRole());
}

// Test method loginUser
TEST_F(AuthServiceTest, LoginUser) {
    // Login thành công (customer)
    auto customer = service->loginUser("customer1", "pass1");
    ASSERT_NE(nullptr, customer);
    EXPECT_EQ("customer1", customer->getUsername());
    EXPECT_EQ(Role::CUSTOMER, customer->getRole());
    
    // Login thành công (admin)
    auto admin = service->loginUser("admin1", "pass2");
    ASSERT_NE(nullptr, admin);
    EXPECT_EQ("admin1", admin->getUsername());
    EXPECT_EQ(Role::ADMIN, admin->getRole());
    
    // Login với username không tồn tại
    auto invalidUser = service->loginUser("nonexistent", "pass");
    EXPECT_EQ(nullptr, invalidUser);
    
    // Login với password sai
    auto invalidPass = service->loginUser("customer1", "wrongpass");
    EXPECT_EQ(nullptr, invalidPass);
}