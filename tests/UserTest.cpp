#include "gtest/gtest.h"
#include "../User.h"

class UserTest : public ::testing::Test {
protected:
    // Không thể tạo User trực tiếp vì nó là abstract class
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Admin> admin;

    void SetUp() override {
        customer = std::make_shared<Customer>("testuser", "password123");
        admin = std::make_shared<Admin>("adminuser", "adminpass");
    }
};

// Test Customer constructor và getters
TEST_F(UserTest, CustomerConstructorAndGetters) {
    EXPECT_EQ("testuser", customer->getUsername());
    EXPECT_EQ("password123", customer->getPassword());
    EXPECT_EQ(Role::CUSTOMER, customer->getRole());
}

// Test Admin constructor và getters
TEST_F(UserTest, AdminConstructorAndGetters) {
    EXPECT_EQ("adminuser", admin->getUsername());
    EXPECT_EQ("adminpass", admin->getPassword());
    EXPECT_EQ(Role::ADMIN, admin->getRole());
}

// Test Admin passkey validation
TEST_F(UserTest, AdminPasskeyValidation) {
    EXPECT_TRUE(Admin::isValidPasskey("23120197"));
    EXPECT_TRUE(Admin::isValidPasskey("23120209"));
    EXPECT_FALSE(Admin::isValidPasskey("wrongpasskey"));
}

// Test toString method
TEST_F(UserTest, UserToStringMethod) {
    std::string customerStr = customer->toString();
    std::string adminStr = admin->toString();
    
    // Kiểm tra xem toString có chứa username không
    EXPECT_NE(std::string::npos, customerStr.find("testuser"));
    EXPECT_NE(std::string::npos, adminStr.find("adminuser"));
}

// Test Copy Constructor
TEST_F(UserTest, CopyConstructor) {
    Customer copiedCustomer(*customer);
    EXPECT_EQ(customer->getUsername(), copiedCustomer.getUsername());
    EXPECT_EQ(customer->getPassword(), copiedCustomer.getPassword());
    EXPECT_EQ(customer->getRole(), copiedCustomer.getRole());
    
    Admin copiedAdmin(*admin);
    EXPECT_EQ(admin->getUsername(), copiedAdmin.getUsername());
    EXPECT_EQ(admin->getPassword(), copiedAdmin.getPassword());
    EXPECT_EQ(admin->getRole(), copiedAdmin.getRole());
}

// Test với trường hợp đặc biệt
TEST_F(UserTest, SpecialCases) {
    // User có username và password trống
    Customer emptyCustomer("", "");
    EXPECT_EQ("", emptyCustomer.getUsername());
    EXPECT_EQ("", emptyCustomer.getPassword());
    
    // User có username và password dài
    std::string longString(1000, 'a');
    Customer longCustomer(longString, longString);
    EXPECT_EQ(longString, longCustomer.getUsername());
    EXPECT_EQ(longString, longCustomer.getPassword());
}