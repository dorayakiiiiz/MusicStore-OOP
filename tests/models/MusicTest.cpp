#include <gtest/gtest.h>
#include "Music.h"

class MusicTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Code chạy trước mỗi test case
        testMusic = Music("Test Song", "Test Artist", "Test Genre", 9.99, 10);
    }

    Music testMusic;
};

TEST_F(MusicTest, GetNameReturnsCorrectName) {
    EXPECT_EQ("Test Song", testMusic.getName());
}

TEST_F(MusicTest, GetArtistReturnsCorrectArtist) {
    EXPECT_EQ("Test Artist", testMusic.getArtist());
}

TEST_F(MusicTest, GetGenreReturnsCorrectGenre) {
    EXPECT_EQ("Test Genre", testMusic.getGenre());
}

TEST_F(MusicTest, GetPriceReturnsCorrectPrice) {
    EXPECT_FLOAT_EQ(9.99f, testMusic.getPrice());
}

TEST_F(MusicTest, GetQuantityReturnsCorrectQuantity) {
    EXPECT_EQ(10, testMusic.getQuantity());
}

TEST_F(MusicTest, UpdatePriceChangesPrice) {
    testMusic.updatePrice(19.99);
    EXPECT_FLOAT_EQ(19.99f, testMusic.getPrice());
}

TEST_F(MusicTest, UpdateQuantityChangesQuantity) {
    testMusic.updateQuantity(20);
    EXPECT_EQ(20, testMusic.getQuantity());
}

TEST_F(MusicTest, ToStringReturnsFormattedString) {
    std::string result = testMusic.toString();
    EXPECT_TRUE(result.find("Test Song") != std::string::npos);
    EXPECT_TRUE(result.find("Test Artist") != std::string::npos);
    EXPECT_TRUE(result.find("Test Genre") != std::string::npos);
    EXPECT_TRUE(result.find("9.99") != std::string::npos);
}

TEST_F(MusicTest, ConstructorInitializesValuesCorrectly) {
    Music newMusic("New Song", "New Artist", "New Genre", 15.99, 5);
    EXPECT_EQ("New Song", newMusic.getName());
    EXPECT_EQ("New Artist", newMusic.getArtist());
    EXPECT_EQ("New Genre", newMusic.getGenre());
    EXPECT_FLOAT_EQ(15.99f, newMusic.getPrice());
    EXPECT_EQ(5, newMusic.getQuantity());
}