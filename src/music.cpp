#include "../headers/music.hpp"

Music::Music(Artist * singer, string title, string filePath, int duration, int year_):
 artist(singer), name(title), path(filePath), durationSeconds(duration), year(year_) {}

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

string Music::getName() {
    return this->name;
}

int Music::getDuration() {
    return this->durationSeconds;
}

int Music::getYear() {
    return this->year;
}

Artist *Music::getArtist() {
    return this->artist;
}
