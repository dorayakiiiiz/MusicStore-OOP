#ifndef _MUSIC_DAO_H_
#define _MUSIC_DAO_H_
#include "Music.h"
#include <vector>

class MusicDAO {
public:
    static void loadItems(std::vector<Music>&);
    static void saveItems(const std::vector<Music>&);
};

#endif