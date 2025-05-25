#include "gtest/gtest.h"
#include "../DatabaseConnector.h"
#include <memory>

// These tests require an actual database connection.
// In a real testing environment, you would use a test database
// or mock the ODBC interfaces.

class DatabaseConnectorTest : public ::testing::Test {
protected:
    DatabaseConnector* connector;
    
    void SetUp() override {
        connector = DatabaseConnector::getInstance();
    }
    
    void TearDown() override {
        // Don't delete singleton
    }
};

// Test singleton pattern
TEST_F(DatabaseConnectorTest, GetInstance) {
    DatabaseConnector* instance1 = DatabaseConnector::getInstance();
    DatabaseConnector* instance2 = DatabaseConnector::getInstance();
    
    EXPECT_EQ(instance1, instance2);
    EXPECT_NE(nullptr, instance1);
}

// Test connection functionality
// Note: This requires actual database access, so may fail in some environments
TEST_F(DatabaseConnectorTest, EnsureConnected) {
    // This will attempt a real connection
    bool connected = connector->ensureConnected();
    
    // If connected, verify state
    if (connected) {
        EXPECT_TRUE(connector->isConnected());
        EXPECT_NE(nullptr, connector->getConnection());
        
        // Test connection
        EXPECT_TRUE(connector->testConnection());
    } else {
        // If connection failed, skip the test
        GTEST_SKIP() << "Database connection failed - skipping test";
    }
}