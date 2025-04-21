#ifndef _MUSIC_ITEM_H_
#define _MUSIC_ITEM_H_

#include <iostream>
#include <string>

using std::string;

class MusicItem {
private:
    string name;
    string artist;
    string genre;
    float price;
    int quantity;

public:
    MusicItem(const string&, const string&, const string&, const float&, const int&);
    ~MusicItem() = default;

public:
    string getName() const;
    string getArtist() const;
    string getGenre() const;
    float getPrice() const;
    int getQuantity() const;
    
    void displayItems();
    void updatePrice(const float&);
    void updateQuantity(const int&);

    bool operator==(const MusicItem&) const;
};

#endif