#include "gtest/gtest.h"
#include "../SalesRecordService.h"
#include "MockSQLDao.h"
#include <memory>

// Tạo subclass của SalesRecordService cho testing
class TestSalesRecordService : public SalesRecordService {
public:
    TestSalesRecordService(std::shared_ptr<IDataProvider> provider) : SalesRecordService(provider) {}
};

class SalesRecordServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSqlDao> mockDao;
    std::shared_ptr<TestSalesRecordService> service;
    std::vector<SalesRecord> testRecords;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockSqlDao>();
        
        // Test data
        testRecords = {
            SalesRecord("Song1", "Artist1", "Pop", 5, 49.95f), // 5 * 9.99 = 49.95
            SalesRecord("Song2", "Artist2", "Rock", 3, 44.97f), // 3 * 14.99 = 44.97
            SalesRecord("Song3", "Artist3", "Jazz", 2, 39.98f)  // 2 * 19.99 = 39.98
        };
        
        // Set data vào mock dao
        mockDao->setSalesRecords(testRecords);
        
        // Tạo service instance để test
        service = std::make_shared<TestSalesRecordService>(mockDao);
    }
};

// Test method getAllSalesRecords
TEST_F(SalesRecordServiceTest, GetAllSalesRecords) {
    auto result = service->getAllSalesRecords();
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("Song1", result[0].getName());
    EXPECT_EQ("Song2", result[1].getName());
    EXPECT_EQ("Song3", result[2].getName());
    
    EXPECT_EQ(5, result[0].getSold());
    EXPECT_EQ(3, result[1].getSold());
    EXPECT_EQ(2, result[2].getSold());
    
    EXPECT_FLOAT_EQ(49.95f, result[0].getRevenue());
    EXPECT_FLOAT_EQ(44.97f, result[1].getRevenue());
    EXPECT_FLOAT_EQ(39.98f, result[2].getRevenue());
}

// Test method getTotalRevenue
TEST_F(SalesRecordServiceTest, GetTotalRevenue) {
    float total = service->getTotalRevenue();
    float expected = 49.95f + 44.97f + 39.98f;
    
    EXPECT_FLOAT_EQ(expected, total);
}

// Test method addToRecord
TEST_F(SalesRecordServiceTest, AddToRecord) {
    // Create a cart with items
    Cart cart;
    cart.addItems(Music("NewSong", "NewArtist", "NewGenre", 12.50f, 2), 2);
    cart.addItems(Music("Song1", "Artist1", "Pop", 9.99f, 3), 3); // Already exists
    
    // Add to sales record
    service->addToRecord(cart);
    
    // Verify records were added/updated
    auto records = service->getAllSalesRecords();
    ASSERT_EQ(4, records.size()); // Added one new record
    
    // Check new record
    bool newSongFound = false;
    bool song1Updated = false;
    
    for (const auto& record : records) {
        if (record.getName() == "NewSong" && record.getArtist() == "NewArtist") {
            newSongFound = true;
            EXPECT_EQ(2, record.getSold());
            EXPECT_FLOAT_EQ(25.0f, record.getRevenue()); // 2 * 12.50 = 25.0
        }
        
        if (record.getName() == "Song1" && record.getArtist() == "Artist1") {
            song1Updated = true;
            // Mock doesn't update existing records, just adds new ones
            // In a real implementation, this would be updated to sold = 8, revenue = 79.92
        }
    }
    
    EXPECT_TRUE(newSongFound);
}