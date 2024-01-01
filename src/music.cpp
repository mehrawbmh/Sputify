#include "../headers/music.hpp"
#include <sstream>
#include <istream>
#include <stdexcept>
#include <iostream>

using namespace std;

Music::Music(Artist* singer, string title, string filePath, string duration, int year_, string album_):
 artist(singer), name(title), path(filePath), timeDuration(duration), year(year_), album(album_) {
    this->tags = {};
 }

bool Music::isDeleted() {
    return this->deleted;
}

void Music::setAsDeleted() {
    this->deleted = true;
}

void Music::setId(int id_) {
    this->id = id_;
}

int Music::getId() {
    return this->id;
}

void Music::addTag(Tag *tag) {
    this->tags.push_back(tag);
}

vector<Tag*> Music::getTags() {
    return this->tags;
}

string Music::getName() {
    return this->name;
}

string Music::getAlbum() {
    return this->album;
}

string Music::getDuration() {
    return this->timeDuration;
}

int Music::getYear() {
    return this->year;
}

Artist* Music::getArtist() {
    return this->artist;
}

int Music::getDurationInSeconds() {
    string durationFormatted = this->timeDuration;

    if (durationFormatted.size() != 8) {
        throw std::logic_error("bad format for music time!");
    }

    string hours = durationFormatted.substr(0,2);
    string minutes = durationFormatted.substr(3,2);
    string seconds = durationFormatted.substr(6,2);

    int result = (stoi(hours) * 3600) + (stoi(minutes) * 60) + stoi(seconds);
    return result;
}

string Music::formatSecondsToTime(int seconds) {
    int hour = seconds / 3600;
    string hours = (hour > 9) ? to_string(hour) : ("0" + to_string(hour));

    int minute = seconds % 3600;
    minute = minute / 60;
    string minutes = (minute > 9) ? to_string(minute) : ("0" + to_string(minute));

    seconds = seconds % 60;
    string secondsString = (seconds > 9) ? to_string(seconds) : ("0" + to_string(seconds));

    return hours + ":" + minutes + ":" + secondsString;
}
