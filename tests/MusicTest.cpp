#include "gtest/gtest.h"
#include "../Music.h"
#include <string>
#include <sstream>

class MusicTest : public ::testing::Test {
protected:
    Music defaultMusic;
    Music testMusic;

    void SetUp() override {
        testMusic = Music("Test Song", "Test Artist", "Test Genre", 9.99f, 10);
    }
};

// Test constructor mặc định
TEST_F(MusicTest, DefaultConstructor) {
    EXPECT_EQ("", defaultMusic.getName());
    EXPECT_EQ("", defaultMusic.getArtist());
    EXPECT_EQ("", defaultMusic.getGenre());
    EXPECT_FLOAT_EQ(0.0f, defaultMusic.getPrice());
    EXPECT_EQ(0, defaultMusic.getQuantity());
}

// Test constructor với tham số
TEST_F(MusicTest, ParameterizedConstructor) {
    EXPECT_EQ("Test Song", testMusic.getName());
    EXPECT_EQ("Test Artist", testMusic.getArtist());
    EXPECT_EQ("Test Genre", testMusic.getGenre());
    EXPECT_FLOAT_EQ(9.99f, testMusic.getPrice());
    EXPECT_EQ(10, testMusic.getQuantity());
}

// Test các getters
TEST_F(MusicTest, Getters) {
    EXPECT_EQ("Test Song", testMusic.getName());
    EXPECT_EQ("Test Artist", testMusic.getArtist());
    EXPECT_EQ("Test Genre", testMusic.getGenre());
    EXPECT_FLOAT_EQ(9.99f, testMusic.getPrice());
    EXPECT_EQ(10, testMusic.getQuantity());
}

// Test các update methods
TEST_F(MusicTest, UpdateMethods) {
    testMusic.updatePrice(19.99f);
    EXPECT_FLOAT_EQ(19.99f, testMusic.getPrice());
    
    testMusic.updateQuantity(20);
    EXPECT_EQ(20, testMusic.getQuantity());
}

// Test toString method
TEST_F(MusicTest, ToStringMethod) {
    std::string expected = "Test Song - Test Artist - Test Genre - 9.99 - 10";
    EXPECT_EQ(expected, testMusic.toString());
}

// Test operator==
TEST_F(MusicTest, EqualityOperator) {
    Music sameMusicDifferentDetails("Test Song", "Test Artist", "Different Genre", 19.99f, 5);
    Music differentMusic("Different Song", "Test Artist", "Test Genre", 9.99f, 10);
    
    // Theo code của bạn, == so sánh theo name và artist
    EXPECT_TRUE(testMusic == sameMusicDifferentDetails);
    EXPECT_FALSE(testMusic == differentMusic);
}