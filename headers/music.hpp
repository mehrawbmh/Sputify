#ifndef SPUTIFY_MUSIC_HPP
#define SPUTIFY_MUSIC_HPP

#include "artist.hpp"
#include "tag.hpp"
#include <string>
#include <vector>

using namespace std;

class Music final {
private:
    int id;
    Artist* artist;
    vector<Tag*> tags;
    string name;
    int year;
    string path;
    int durationSeconds;
    bool deleted = false;
    
public:
    Music(Artist* singer, string title, string filePath, int duration, int year);
    bool isDeleted();
    void setAsDeleted();
    void setId(int id_);
    int getId();
    vector<Tag*> getTags();
    void addTag(Tag*);
    string getName();
    int getDuration();
    int getYear();
    Artist* getArtist();
};

#endif //SPUTIFY_MUSIC_HPP
