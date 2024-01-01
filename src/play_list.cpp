#include "../headers/play_list.hpp"

PlayList::PlayList(string title_, int user): title(title_), userId(user) {}

string PlayList::getTitle() {
    return this->title;
}

int PlayList::getUserId() {
    return this->userId;
}

int PlayList::getId() {
    return this->id;
}

void PlayList::setId(int id_) {
    this->id = id_;
}

void PlayList::addMusic(Music* music) {
    this->musics.push_back(music);
}

string PlayList::getPlaylistDuration() {
    int sum = 0;
    for (Music* music: this->musics) {
        sum += music->getDurationInSeconds();
    }

    return to_string(sum);
}
