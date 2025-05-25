#include "gtest/gtest.h"
#include "../MusicService.h"
#include "../SearchFactory.h"
#include "MockDao.h"
#include <memory>

// Tạo subclass của MusicService cho testing
class TestMusicService : public MusicService {
public:
    TestMusicService(std::shared_ptr<IDataProvider> provider) : MusicService(provider) {}
};

class MusicServiceTest : public ::testing::Test {
protected:
    std::shared_ptr<MockDao> mockDao;
    std::shared_ptr<TestMusicService> service;
    
    void SetUp() override {
        // Tạo mock dao
        mockDao = std::make_shared<MockDao>();
        
        // Test data
        std::vector<Music> testItems = {
            Music("Song1", "Artist1", "Pop", 9.99f, 5),
            Music("Song2", "Artist2", "Rock", 14.99f, 3),
            Music("Song3", "Artist1", "Jazz", 19.99f, 2)
        };
        
        // Set data vào mock dao
        mockDao->setMusicItems(testItems);
        
        // Tạo service instance để test
        service = std::make_shared<TestMusicService>(mockDao);
    }
};

// Test method getAllMusic
TEST_F(MusicServiceTest, GetAllMusic) {
    auto result = service->getAllMusic();
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("Song1", result[0].getName());
    EXPECT_EQ("Song2", result[1].getName());
    EXPECT_EQ("Song3", result[2].getName());
}

// Test method searchMusic với tiêu chí NAME
TEST_F(MusicServiceTest, SearchMusicByName) {
    auto allItems = service->getAllMusic();
    auto result = service->searchMusic(allItems, SearchType::NAME, "Song1");
    
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("Song1", result[0].getName());
}

// Test method searchMusic với tiêu chí ARTIST
TEST_F(MusicServiceTest, SearchMusicByArtist) {
    auto allItems = service->getAllMusic();
    auto result = service->searchMusic(allItems, SearchType::ARTIST, "Artist1");
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("Song1", result[0].getName());
    EXPECT_EQ("Song3", result[1].getName());
}

// Test method searchMusic với tiêu chí GENRE
TEST_F(MusicServiceTest, SearchMusicByGenre) {
    auto allItems = service->getAllMusic();
    auto result = service->searchMusic(allItems, SearchType::GENRE, "Rock");
    
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("Song2", result[0].getName());
}

// Test method addMusicItem
TEST_F(MusicServiceTest, AddMusicItem) {
    Music newItem("New Song", "New Artist", "Pop", 24.99f, 10);
    
    EXPECT_TRUE(service->addMusicItem(newItem));
    
    auto allItems = service->getAllMusic();
    ASSERT_EQ(4, allItems.size());
    EXPECT_EQ("New Song", allItems[3].getName());
}

// Test method removeMusicItem
TEST_F(MusicServiceTest, RemoveMusicItem) {
    EXPECT_TRUE(service->removeMusicItem(1));
    
    auto allItems = service->getAllMusic();
    ASSERT_EQ(2, allItems.size());
    EXPECT_EQ("Song2", allItems[0].getName());
}

// Test method updateMusicItemPrice
TEST_F(MusicServiceTest, UpdateMusicItemPrice) {
    EXPECT_TRUE(service->updateMusicItemPrice(1, 29.99f));
    
    auto allItems = service->getAllMusic();
    EXPECT_FLOAT_EQ(29.99f, allItems[0].getPrice());
}

// Test method removeSoldOutItems
TEST_F(MusicServiceTest, RemoveSoldOutItems) {
    // Add item with zero quantity
    mockDao->setMusicItems({
        Music("Song1", "Artist1", "Pop", 9.99f, 5),
        Music("Song2", "Artist2", "Rock", 14.99f, 0), // Sold out
        Music("Song3", "Artist1", "Jazz", 19.99f, 2)
    });
    
    service->removeSoldOutItems();
    
    auto allItems = service->getAllMusic();
    ASSERT_EQ(2, allItems.size());
    EXPECT_EQ("Song1", allItems[0].getName());
    EXPECT_EQ("Song3", allItems[1].getName());
}