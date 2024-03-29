#ifndef SPUTIFY_MUSIC_HPP
#define SPUTIFY_MUSIC_HPP

#include <string>
#include <vector>

#include "entity.hpp"
#include "artist.hpp"
#include "tag.hpp"

using namespace std;

const int HOUR_SECONDS = 3600;
const int MAX_ONE_DIGIT_NUMBER = 9;
const int MINUTE_SECONDS = 60;

class Music: public Entity {
private:
    int id;
    Artist* artist;
    vector<Tag*> tags;
    string name;
    string album;
    int year;
    string path;
    string timeDuration;
    int likesCount;

public:
    Music(Artist* singer, string title, string filePath, string duration, int year, string album);
    void setId(int id_);
    int getId() const;
    vector<Tag*> getTags();
    void addTag(Tag*);
    string getName();
    string getAlbum();
    string getDuration();
    string getPath();
    int getYear() const;
    Artist* getArtist();
    int getDurationInSeconds();
    int getLikesCount();
    void incrementLikes();
    void decrementLikes();
    static string formatSecondsToTime(int seconds);
};

#endif //SPUTIFY_MUSIC_HPP
