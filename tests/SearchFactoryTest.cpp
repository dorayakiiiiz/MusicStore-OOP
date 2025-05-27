#include "gtest/gtest.h"
#include "../source/factories/SearchFactory.h"
#include "../source/strategies/Search.h"
#include <memory>

class SearchFactoryTest : public ::testing::Test {
protected:
    SearchFactory factory;
};

// Test createSearch cho các loại search
TEST_F(SearchFactoryTest, CreateSearchByType) {
    // Test với NAME search
    auto nameSearch = factory.createSearch(SearchType::NAME);
    ASSERT_NE(nullptr, nameSearch);
    EXPECT_TRUE(dynamic_cast<NameSearch*>(nameSearch.get()) != nullptr);
    
    // Test với ARTIST search
    auto artistSearch = factory.createSearch(SearchType::ARTIST);
    ASSERT_NE(nullptr, artistSearch);
    EXPECT_TRUE(dynamic_cast<ArtistSearch*>(artistSearch.get()) != nullptr);
    
    // Test với GENRE search
    auto genreSearch = factory.createSearch(SearchType::GENRE);
    ASSERT_NE(nullptr, genreSearch);
    EXPECT_TRUE(dynamic_cast<GenreSearch*>(genreSearch.get()) != nullptr);
}

// Test với invalid search type
TEST_F(SearchFactoryTest, CreateSearchInvalidType) {
    // Tạo một SearchType không hợp lệ (ngoài enum)
    SearchType invalidType = static_cast<SearchType>(999);
    auto invalidSearch = factory.createSearch(invalidType);
    
    // Expected: nullptr hoặc exception
    EXPECT_EQ(nullptr, invalidSearch);
}