#include "gtest/gtest.h"
#include "../SalesRecord.h"

class SalesRecordTest : public ::testing::Test {
protected:
    SalesRecord defaultRecord;
    SalesRecord testRecord;

    void SetUp() override {
        testRecord = SalesRecord("Test Song", "Test Artist", "Pop", 10, 99.90f);
    }
};

// Test constructor mặc định
TEST_F(SalesRecordTest, DefaultConstructor) {
    EXPECT_EQ("", defaultRecord.getName());
    EXPECT_EQ("", defaultRecord.getArtist());
    EXPECT_EQ("", defaultRecord.getGenre());
    EXPECT_EQ(0, defaultRecord.getSold());
    EXPECT_FLOAT_EQ(0.0f, defaultRecord.getRevenue());
}

// Test constructor với tham số
TEST_F(SalesRecordTest, ParameterizedConstructor) {
    EXPECT_EQ("Test Song", testRecord.getName());
    EXPECT_EQ("Test Artist", testRecord.getArtist());
    EXPECT_EQ("Pop", testRecord.getGenre());
    EXPECT_EQ(10, testRecord.getSold());
    EXPECT_FLOAT_EQ(99.90f, testRecord.getRevenue());
}

// Test các getters
TEST_F(SalesRecordTest, Getters) {
    EXPECT_EQ("Test Song", testRecord.getName());
    EXPECT_EQ("Test Artist", testRecord.getArtist());
    EXPECT_EQ("Pop", testRecord.getGenre());
    EXPECT_EQ(10, testRecord.getSold());
    EXPECT_FLOAT_EQ(99.90f, testRecord.getRevenue());
}

// Test với giá trị đặc biệt
TEST_F(SalesRecordTest, SpecialValues) {
    // Record với lượng bán = 0
    SalesRecord zeroSales("Zero Sales", "Artist", "Genre", 0, 0.0f);
    EXPECT_EQ(0, zeroSales.getSold());
    EXPECT_FLOAT_EQ(0.0f, zeroSales.getRevenue());
    
    // Record với doanh thu âm (không lí tưởng nhưng nên xử lí được)
    SalesRecord negativeRevenue("Neg Rev", "Artist", "Genre", 5, -10.5f);
    EXPECT_FLOAT_EQ(-10.5f, negativeRevenue.getRevenue());
    
    // Record với lượng bán âm (không lí tưởng nhưng nên xử lí được)
    SalesRecord negativeSold("Neg Sold", "Artist", "Genre", -3, 30.0f);
    EXPECT_EQ(-3, negativeSold.getSold());
}