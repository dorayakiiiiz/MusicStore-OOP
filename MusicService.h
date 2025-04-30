#ifndef _MUSIC_SERVICE_H_
#define _MUSIC_SERVICE_H_

#include "Music.h"
#include <vector>
using std::vector;
class MusicService {
public:
    static void addMusicItem(vector<Music>&, const Music&);
    static bool removeMusicItem(vector<Music>&, int);
    static void updateMusicItemPrice(vector<Music>&, int, float);
    static vector<Music> searchMusicItem(const vector<Music>&, const string&);

};

#endif