#include "Search.h"
#include "utils.h"

vector<Music> NameSearch::search(const vector<Music>& items, const string& keyword) const {
    vector<Music> results;
    for (const auto& item : items) {
        string lowerName = toLower(item.getName());
        string lowerKeyword = toLower(keyword);
        if (lowerName.find(lowerKeyword) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

vector<Music> ArtistSearch::search(const vector<Music>& items, const string& keyword) const {
    vector<Music> results;
    for (const auto& item : items) {
        string lowerArtist = toLower(item.getArtist());
        string lowerKeyword = toLower(keyword);
        if (lowerArtist.find(lowerKeyword) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

vector<Music> GenreSearch::search(const vector<Music>& items, const string& keyword) const {
    vector<Music> results;
    for (const auto& item : items) {
        string lowerGenre = toLower(item.getGenre());
        string lowerKeyword = toLower(keyword);
        if (lowerGenre.find(lowerKeyword) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

