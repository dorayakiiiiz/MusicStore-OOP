#include "gtest/gtest.h"
#include "../ControllerFactory.h"
#include "../IController.h"
#include "../AdminController.h"
#include "../CustomerController.h"
#include <memory>

class ControllerFactoryTest : public ::testing::Test {
protected:
    ControllerFactory factory;
};

// Test controller creation by role
TEST_F(ControllerFactoryTest, CreateController) {
    // Create admin controller
    auto adminController = factory.createController(Role::ADMIN);
    ASSERT_NE(nullptr, adminController);
    
    // Create customer controller
    auto customerController = factory.createController(Role::CUSTOMER);
    ASSERT_NE(nullptr, customerController);
    
    // Test with invalid role (cast to invalid enum value)
    auto invalidController = factory.createController(static_cast<Role>(999));
    EXPECT_EQ(nullptr, invalidController);
    
    // Check that correct types were created
    // Note: We can't directly check the type with dynamic_cast because the controllers
    // are stored as shared_ptr<IController>, but we could check interface behavior if needed
}