#ifndef _MUSIC_ITEM_H_
#define _MUSIC_ITEM_H_

#include <iostream>
#include <string>

using std::string;

class MusicItem {
private:
    int id;
    string name;
    string artist;
    string genre;
    float price;
    int quantity;

public:
    MusicItem(const int&, const string&, const string&, const string&, const float&, const int&);
    ~MusicItem() = default;

public:
    int getID() const;
    string getName() const;
    string getArtist() const;
    string getGenre() const;
    float getPrice() const;
    int getQuantity() const;
    
    void displayItems();
    void updatePrice(const float&);
    void updateQuantity(const int&);
};

#endif