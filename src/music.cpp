#include "../headers/music.hpp"
#include "../headers/format_exception.hpp"

#include <stdexcept>
#include <iostream>
#include <utility>

using namespace std;

Music::Music(Artist* singer, string title, string filePath, string duration, int year_, string album_):
 artist(singer), name(std::move(title)), path(std::move(filePath)), timeDuration(std::move(duration)),
 year(year_), album(std::move(album_)), likesCount(0), tags({}) {}

void Music::setId(int id_) {
    this->id = id_;
}

int Music::getId() const {
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

string Music::getPath() {
    return this->path;
}

int Music::getYear() const {
    return this->year;
}

Artist* Music::getArtist() {
    return this->artist;
}

int Music::getDurationInSeconds() {
    string durationFormatted = this->timeDuration;

    if (durationFormatted.size() != 8) {
        throw FormatException("bad format for music time!");
    }

    string hours = durationFormatted.substr(0,2);
    string minutes = durationFormatted.substr(3,2);
    string seconds = durationFormatted.substr(6,2);

    int result = (stoi(hours) * HOUR_SECONDS) + (stoi(minutes) * MINUTE_SECONDS) + stoi(seconds);
    return result;
}

string Music::formatSecondsToTime(int seconds) {
    int hour = seconds / HOUR_SECONDS;
    string hours = (hour > MAX_ONE_DIGIT_NUMBER) ? to_string(hour) : ("0" + to_string(hour));

    int minute = seconds % HOUR_SECONDS;
    minute = minute / MINUTE_SECONDS;
    string minutes = (minute > MAX_ONE_DIGIT_NUMBER) ? to_string(minute) : ("0" + to_string(minute));

    seconds = seconds % MINUTE_SECONDS;
    string secondsString = (seconds > MAX_ONE_DIGIT_NUMBER) ? to_string(seconds) : ("0" + to_string(seconds));

    return hours + ":" + minutes + ":" + secondsString;
}

void Music::incrementLikes() {
    this->likesCount++;
}

void Music::decrementLikes() {
    this->likesCount--;
}

int Music::getLikesCount() {
    return this->likesCount;
}
