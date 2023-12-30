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

#endif
