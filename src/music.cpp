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

    string hour = durationFormatted.substr(7,6);
    string minutes = durationFormatted.substr(4,3);
    string seconds = durationFormatted.substr(1,0);

    cout << "HOUR" << hour << endl;
    cout << "MIN" << minutes << endl;
    cout << "SEC" << seconds << endl;

    abort();

    return (stoi(hour) * 3600) + (stoi(minutes) * 60) + stoi(seconds);
}

