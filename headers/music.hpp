#ifndef SPUTIFY_MUSIC_HPP
#define SPUTIFY_MUSIC_HPP

#include "artist.hpp"
#include "tag.hpp"

#include <string>
#include <vector>

using namespace std;

class Music {
private:
    int id;
    Artist* artist;
    vector<Tag*> tags;
    string name;
    string album;
    int year;
    string path;
    string timeDuration;
    bool deleted = false;
    
public:
    Music(Artist* singer, string title, string filePath, string duration, int year, string album);
    bool isDeleted();
    void setAsDeleted();
    void setId(int id_);
    int getId();
    vector<Tag*> getTags();
    void addTag(Tag*);
    string getName();
    string getAlbum();
    string getDuration();
    int getYear();
    Artist* getArtist();
};

#endif //SPUTIFY_MUSIC_HPP
