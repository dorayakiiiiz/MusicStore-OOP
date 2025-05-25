#include "gtest/gtest.h"
#include "../IController.h"
#include <memory>
#include <string>

// Mock implementation of IController for testing
class MockController : public IController {
private:
    bool wasMenuCalled;
    std::string controllerName;
    
public:
    MockController(const std::string& name) : wasMenuCalled(false), controllerName(name) {}
    
    void menu(std::shared_ptr<User>& currentUser) override {
        wasMenuCalled = true;
    }
    
    bool menuWasCalled() const {
        return wasMenuCalled;
    }
    
    std::string getName() const {
        return controllerName;
    }
};

class ControllerPatternTest : public ::testing::Test {
protected:
    std::shared_ptr<User> testUser;
    
    void SetUp() override {
        testUser = std::make_shared<Customer>("testuser", "password");
    }
};

// Test controller interface
TEST_F(ControllerPatternTest, ControllerInterface) {
    auto controller = std::make_shared<MockController>("TestController");
    
    // Check initial state
    EXPECT_FALSE(controller->menuWasCalled());
    EXPECT_EQ("TestController", controller->getName());
    
    // Call menu and verify it was called
    controller->menu(testUser);
    EXPECT_TRUE(controller->menuWasCalled());
    
    // Verify user was not changed (this would depend on the controller implementation)
    EXPECT_EQ("testuser", testUser->getUsername());
}