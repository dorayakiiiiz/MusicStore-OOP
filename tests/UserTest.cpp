#include "gtest/gtest.h"
#include "../User.h"

class UserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Không cần thiết lập gì đặc biệt
    }
};

// Test constructor và getters của Customer
TEST_F(UserTest, CustomerConstructorAndGetters) {
    Customer customer("testuser", "password123");
    
    EXPECT_EQ("testuser", customer.getUsername());
    EXPECT_EQ("password123", customer.getPassword());
    EXPECT_EQ(Role::CUSTOMER, customer.getRole());
}

// Test constructor và getters của Admin
TEST_F(UserTest, AdminConstructorAndGetters) {
    Admin admin("adminuser", "adminpass");
    
    EXPECT_EQ("adminuser", admin.getUsername());
    EXPECT_EQ("adminpass", admin.getPassword());
    EXPECT_EQ(Role::ADMIN, admin.getRole());
}

// Test validate passkey của Admin
TEST_F(UserTest, AdminPasskeyValidation) {
    EXPECT_TRUE(Admin::isValidPasskey("23120197"));
    EXPECT_TRUE(Admin::isValidPasskey("23120209"));
    EXPECT_FALSE(Admin::isValidPasskey("wrongpasskey"));
}

// Test toString method
TEST_F(UserTest, UserToStringMethod) {
    Customer customer("testuser", "password123");
    Admin admin("adminuser", "adminpass");
    
    // ToString should include username in both cases
    EXPECT_NE(std::string::npos, customer.toString().find("testuser"));
    EXPECT_NE(std::string::npos, admin.toString().find("adminuser"));
}

// Test copy constructor cho Customer
TEST_F(UserTest, CustomerCopyConstructor) {
    Customer original("testuser", "password123");
    Customer copy(original);
    
    EXPECT_EQ(original.getUsername(), copy.getUsername());
    EXPECT_EQ(original.getPassword(), copy.getPassword());
    EXPECT_EQ(original.getRole(), copy.getRole());
}

// Test copy constructor cho Admin
TEST_F(UserTest, AdminCopyConstructor) {
    Admin original("adminuser", "adminpass");
    Admin copy(original);
    
    EXPECT_EQ(original.getUsername(), copy.getUsername());
    EXPECT_EQ(original.getPassword(), copy.getPassword());
    EXPECT_EQ(original.getRole(), copy.getRole());
}