#include "gtest/gtest.h"
#include "../SearchFactory.h"
#include "../Search.h"
#include <memory>

class SearchFactoryTest : public ::testing::Test {
protected:
    SearchFactory factory;

    void SetUp() override {
        // Factory được khởi tạo mặc định trong constructor
    }
};

// Test tạo các chiến lược tìm kiếm
TEST_F(SearchFactoryTest, CreateSearch) {
    // Tạo strategy NAME
    auto nameSearch = factory.createSearch(SearchType::NAME);
    ASSERT_NE(nullptr, nameSearch);
    
    // Tạo strategy ARTIST
    auto artistSearch = factory.createSearch(SearchType::ARTIST);
    ASSERT_NE(nullptr, artistSearch);
    
    // Tạo strategy GENRE
    auto genreSearch = factory.createSearch(SearchType::GENRE);
    ASSERT_NE(nullptr, genreSearch);
    
    // Kiểm tra các strategy có hoạt động đúng không
    std::vector<Music> testItems = {
        Music("Test Song", "Test Artist", "Test Genre", 9.99f, 5)
    };
    
    // NAME search should find by name
    auto nameResults = nameSearch->search(testItems, "Test Song");
    EXPECT_EQ(1, nameResults.size());
    
    // ARTIST search should find by artist
    auto artistResults = artistSearch->search(testItems, "Test Artist");
    EXPECT_EQ(1, artistResults.size());
    
    // GENRE search should find by genre
    auto genreResults = genreSearch->search(testItems, "Test Genre");
    EXPECT_EQ(1, genreResults.size());
}

// Test với search type không hợp lệ
TEST_F(SearchFactoryTest, InvalidSearchType) {
    // Thử tạo strategy với giá trị không hợp lệ (cast enum)
    auto invalidSearch = factory.createSearch(static_cast<SearchType>(999));
    EXPECT_EQ(nullptr, invalidSearch);
}