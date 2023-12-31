#ifndef SPUTIFY_PLAY_LIST_HPP
#define SPUTIFY_PLAY_LIST_HPP

#include <string>
#include <vector>
#include "music.hpp"

using namespace std;

class PlayList {
private:
    vector<Music*> musics;
    string title;
    int userId;
    int id;

public:
    PlayList(string title, int user);
    string getTitle();
    int getUserId();
    void setId(int id_);
    int getId();
    void addMusic(Music* music);
};

#endif //SPUTIFY_PLAY_LIST_HPP
