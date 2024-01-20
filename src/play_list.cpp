#include "../headers/play_list.hpp"
#include "../headers/format_exception.hpp"

using namespace std;

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
        try {
            sum += music->getDurationInSeconds();
        } catch (FormatException &fex) {
            cout << "ERROR: " << fex.what() << endl;
        }
    }

    return Music::formatSecondsToTime(sum);
}

int PlayList::getSongsCount() {
    int count = 0;
    for (Music* music: this->musics) {
        if (music->isDeleted()) {
            continue;
        }
        count++;
    }

    return count;
}

vector<Music*> PlayList::getSongs() {
    vector<Music*> result;
    for (auto *music: this->musics) {
        if (!music->isDeleted()) {
            result.push_back(music);
        }
    }
    return result;
}
