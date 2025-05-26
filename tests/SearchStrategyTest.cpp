#include "gtest/gtest.h"
#include "../Search.h"
#include "../Music.h"
#include <vector>
#include <memory>

class SearchStrategyTest : public ::testing::Test {
protected:
    std::vector<Music> testItems;
    std::shared_ptr<ISearch> nameSearch;
    std::shared_ptr<ISearch> artistSearch;
    std::shared_ptr<ISearch> genreSearch;

    void SetUp() override {
        // Create test data
        testItems = {
            Music("Happy Song", "John Doe", "Pop", 9.99f, 5),
            Music("Sad Song", "Jane Smith", "Rock", 8.99f, 10),
            Music("Dance Song", "John Doe", "Dance", 7.99f, 15),
            Music("Love Ballad", "Mike Brown", "Pop", 12.99f, 3),
            Music("Rock Anthem", "Jane Smith", "Rock", 11.99f, 7)
        };

        // Initialize search strategies
        nameSearch = std::make_shared<NameSearch>();
        artistSearch = std::make_shared<ArtistSearch>();
        genreSearch = std::make_shared<GenreSearch>();
    }
};

// Test NameSearch
TEST_F(SearchStrategyTest, NameSearch) {
    // Test exact match
    auto result1 = nameSearch->search(testItems, "Happy Song");
    ASSERT_EQ(1, result1.size());
    EXPECT_EQ("Happy Song", result1[0].getName());
    
    // Test partial match
    auto result2 = nameSearch->search(testItems, "Song");
    ASSERT_EQ(3, result2.size());
    
    // Test case insensitivity
    auto result3 = nameSearch->search(testItems, "happy");
    ASSERT_EQ(1, result3.size());
    EXPECT_EQ("Happy Song", result3[0].getName());
    
    // Test no match
    auto result4 = nameSearch->search(testItems, "Non-existent");
    EXPECT_TRUE(result4.empty());
}

// Test ArtistSearch
TEST_F(SearchStrategyTest, ArtistSearch) {
    // Test exact match
    auto result1 = artistSearch->search(testItems, "John Doe");
    ASSERT_EQ(2, result1.size());
    EXPECT_EQ("John Doe", result1[0].getArtist());
    EXPECT_EQ("John Doe", result1[1].getArtist());
    
    // Test partial match
    auto result2 = artistSearch->search(testItems, "Smith");
    ASSERT_EQ(2, result2.size());
    
    // Test case insensitivity
    auto result3 = artistSearch->search(testItems, "john");
    ASSERT_EQ(2, result3.size());
    
    // Test no match
    auto result4 = artistSearch->search(testItems, "Non-existent");
    EXPECT_TRUE(result4.empty());
}

// Test GenreSearch
TEST_F(SearchStrategyTest, GenreSearch) {
    // Test exact match
    auto result1 = genreSearch->search(testItems, "Pop");
    ASSERT_EQ(2, result1.size());
    EXPECT_EQ("Pop", result1[0].getGenre());
    EXPECT_EQ("Pop", result1[1].getGenre());
    
    // Test partial match
    auto result2 = genreSearch->search(testItems, "Ro");
    ASSERT_EQ(2, result2.size());
    
    // Test case insensitivity
    auto result3 = genreSearch->search(testItems, "pop");
    ASSERT_EQ(2, result3.size());
    
    // Test no match
    auto result4 = genreSearch->search(testItems, "Jazz");
    EXPECT_TRUE(result4.empty());
}

// Test Empty Collection
TEST_F(SearchStrategyTest, EmptyCollection) {
    std::vector<Music> emptyItems;
    
    auto result1 = nameSearch->search(emptyItems, "Song");
    EXPECT_TRUE(result1.empty());
    
    auto result2 = artistSearch->search(emptyItems, "Artist");
    EXPECT_TRUE(result2.empty());
    
    auto result3 = genreSearch->search(emptyItems, "Genre");
    EXPECT_TRUE(result3.empty());
}
