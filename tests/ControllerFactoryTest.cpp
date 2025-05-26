#include "gtest/gtest.h"
#include "../ControllerFactory.h"
#include "../AdminController.h"
#include "../CustomerController.h"
#include "../IController.h"
#include <memory>

class ControllerFactoryTest : public ::testing::Test {
protected:
    ControllerFactory factory;
};

// Test createController cho các loại role
TEST_F(ControllerFactoryTest, CreateControllerByRole) {
    // Test với ADMIN role
    auto adminController = factory.createController(Role::ADMIN);
    ASSERT_NE(nullptr, adminController);
    EXPECT_TRUE(dynamic_cast<AdminController*>(adminController.get()) != nullptr);
    
    // Test với CUSTOMER role
    auto customerController = factory.createController(Role::CUSTOMER);
    ASSERT_NE(nullptr, customerController);
    EXPECT_TRUE(dynamic_cast<CustomerController*>(customerController.get()) != nullptr);
}

// Test với invalid role
TEST_F(ControllerFactoryTest, CreateControllerInvalidRole) {
    // Tạo một Role không hợp lệ
    Role invalidRole = static_cast<Role>(999);
    auto invalidController = factory.createController(invalidRole);
    
    // Expected: nullptr
    EXPECT_EQ(nullptr, invalidController);
}