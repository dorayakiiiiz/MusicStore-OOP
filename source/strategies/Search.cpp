#include "Search.h"
#include <algorithm>
#include <cctype>
#include <string>
#include "../ui/utils.h"

using namespace std;

// Searches for music items by name.
// It performs a case-insensitive search.
vector<Music> NameSearch::search(const vector<Music>& items, const string& keyword) const {
    vector<Music> results;
    // Iterate through each music item
    for (const auto& item : items) {
        // Convert both the item's name and the keyword to lowercase for case-insensitive comparison
        string lowerName = toLower(item.getName());
        string lowerKeyword = toLower(keyword);
        // If the lowercase name contains the lowercase keyword, add the item to the results
        if (lowerName.find(lowerKeyword) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

// Searches for music items by artist.
// It performs a case-insensitive search.
vector<Music> ArtistSearch::search(const vector<Music>& items, const string& keyword) const {
    vector<Music> results;
    // Iterate through each music item
    for (const auto& item : items) {
        // Convert both the item's artist and the keyword to lowercase for case-insensitive comparison
        string lowerArtist = toLower(item.getArtist());
        string lowerKeyword = toLower(keyword);
        // If the lowercase artist contains the lowercase keyword, add the item to the results
        if (lowerArtist.find(lowerKeyword) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

// Searches for music items by genre.
// It performs a case-insensitive search.
vector<Music> GenreSearch::search(const vector<Music>& items, const string& keyword) const {
    vector<Music> results;
    // Iterate through each music item
    for (const auto& item : items) {
        // Convert both the item's genre and the keyword to lowercase for case-insensitive comparison
        string lowerGenre = toLower(item.getGenre());
        string lowerKeyword = toLower(keyword);
        // If the lowercase genre contains the lowercase keyword, add the item to the results
        if (lowerGenre.find(lowerKeyword) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}