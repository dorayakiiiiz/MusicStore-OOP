#include "MusicService.h"

void MusicService::addMusicItem(vector<Music>& items, const Music& item) {
    items.push_back(item);
}

bool MusicService::removeMusicItem(vector<Music>& items, int id) {
    if (id < 0 || id >= items.size()) {
        return false;
    }
    items.erase(items.begin() + id);
    return true;
}

void MusicService::updateMusicItemPrice(vector<Music>& items, int id, float price) {
    items[id].updatePrice(price);
}

vector<Music> MusicService::searchMusicItem(const vector<Music>& items, const string& keyword) {
    string lowerKeyword = keyword;
    for (auto& c : lowerKeyword) {
        c = tolower(c);
    }
    vector<Music> results;
    for (int i = 0; i < items.size(); ++i) {
        string lowerName = items[i].getName();
        for (auto& c : lowerName) {
            c = tolower(c);
        }
        if (lowerName.find(lowerKeyword) != string::npos) {
            results.push_back(items[i]);
        }
    }
    return results;
}