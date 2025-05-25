#include "gtest/gtest.h"
#include "../Search.h"
#include "../Music.h"
#include <vector>
#include <memory>

class SearchTest : public ::testing::Test {
protected:
    std::vector<Music> testItems;
    std::shared_ptr<ISearch> nameSearch;
    std::shared_ptr<ISearch> artistSearch;
    std::shared_ptr<ISearch> genreSearch;

    void SetUp() override {
        // Tạo dữ liệu test
        testItems = {
            Music("Happy Song", "John Doe", "Pop", 9.99f, 5),
            Music("Sad Song", "Jane Smith", "Rock", 8.99f, 10),
            Music("Dance Song", "John Doe", "Dance", 7.99f, 15),
            Music("Love Ballad", "Mike Brown", "Pop", 12.99f, 3),
            Music("Rock Anthem", "Jane Smith", "Rock", 11.99f, 7)
        };

        nameSearch = std::make_shared<NameSearch>();
        artistSearch = std::make_shared<ArtistSearch>();
        genreSearch = std::make_shared<GenreSearch>();
    }
};

// Test tìm kiếm theo tên
TEST_F(SearchTest, NameSearch) {
    // Tìm kiếm chính xác
    auto result1 = nameSearch->search(testItems, "Happy Song");
    EXPECT_EQ(1, result1.size());
    EXPECT_EQ("Happy Song", result1[0].getName());
    
    // Tìm kiếm một phần
    auto result2 = nameSearch->search(testItems, "Song");
    EXPECT_EQ(3, result2.size());
    
    // Tìm kiếm không phân biệt hoa thường
    auto result3 = nameSearch->search(testItems, "happy");
    EXPECT_EQ(1, result3.size());
    EXPECT_EQ("Happy Song", result3[0].getName());
    
    // Tìm kiếm không có kết quả
    auto result4 = nameSearch->search(testItems, "Unknown Song");
    EXPECT_TRUE(result4.empty());
}

// Test tìm kiếm theo nghệ sĩ
TEST_F(SearchTest, ArtistSearch) {
    // Tìm kiếm chính xác
    auto result1 = artistSearch->search(testItems, "John Doe");
    EXPECT_EQ(2, result1.size());
    
    // Tìm kiếm một phần
    auto result2 = artistSearch->search(testItems, "Smith");
    EXPECT_EQ(2, result2.size());
    
    // Tìm kiếm không phân biệt hoa thường
    auto result3 = artistSearch->search(testItems, "john");
    EXPECT_EQ(2, result3.size());
    
    // Tìm kiếm không có kết quả
    auto result4 = artistSearch->search(testItems, "Unknown Artist");
    EXPECT_TRUE(result4.empty());
}

// Test tìm kiếm theo thể loại
TEST_F(SearchTest, GenreSearch) {
    // Tìm kiếm chính xác
    auto result1 = genreSearch->search(testItems, "Pop");
    EXPECT_EQ(2, result1.size());
    
    // Tìm kiếm một phần
    auto result2 = genreSearch->search(testItems, "Ro");
    EXPECT_EQ(2, result2.size());
    
    // Tìm kiếm không phân biệt hoa thường
    auto result3 = genreSearch->search(testItems, "pop");
    EXPECT_EQ(2, result3.size());
    
    // Tìm kiếm không có kết quả
    auto result4 = genreSearch->search(testItems, "Jazz");
    EXPECT_TRUE(result4.empty());
}