#include "../headers/db.hpp"
#include "../headers/unique_exception.hpp"

#include <stdexcept>
#include <iostream>
#include <cassert>

using namespace std;

int Database::addNormalUser(User *user) {
    int lastId = this->getAllUsers().size();
    user->setId(lastId + 1);

    this->allUsers.push_back(user);
    this->normalUsers.push_back(user);

    return 200;
}

void Database::setCurrentUser(BaseUser* user) {
    this->currentUser = user;
}

BaseUser* Database::getCurrentUser() {
    return this->currentUser;
}

int Database::addArtist(Artist *artist) {
    int lastId = static_cast<int>(this->getAllUsers().size());
    artist->setId(lastId + 1);

    this->allUsers.push_back(artist);
    this->artists.push_back(artist);
    
    return 200;
}

vector<BaseUser*> Database::getAllUsers() {
    return this->allUsers;
}

vector<User*> Database::getNormalUsers() {
    return this->normalUsers;
}

vector<Artist*> Database::getArtistUsers() {
    return this->artists;
}

BaseUser* Database::findOneUserById(const int &id) {
    for (auto baseUser: allUsers) {
        if (baseUser->getId() == id) {
            return baseUser;
        }
    }
    return nullptr;
}

BaseUser* Database::findOneUserByUsername(const string &username) {
    for (auto baseUser: allUsers) {
        if (baseUser->getUsername() == username) {
            return baseUser;
        }
    }
    return nullptr;
}

vector<BaseUser*> Database::findManyUsersByIds(const vector<int> &ids) {
    vector<BaseUser*> result;
    for (const int &id: ids) {
        for (auto *user: allUsers) {
            if (user->getId() == id) {
                if (!user->isDeleted()) {
                    result.push_back(user);
                }
                break;
            }
        }
    }
    return result;
}


vector<Music *> Database::getAllMusics(bool excludeDeleted) {
    if (!excludeDeleted) {
        return this->musics;
    }

    vector<Music*> result;
    for (Music* mus: this->musics) {
        if (!mus->isDeleted()) {
            result.push_back(mus);
        }
    }
    return result;
}

void Database::addMusic(Music *music) {
    int lastId = static_cast<int>(this->musics.size());
    music->setId(lastId + 1);
    this->musics.push_back(music);
}

void Database::addPlaylist(PlayList* pl) {
    assert(!pl->isDeleted());

    for (PlayList* playlist: playlists) {
        if (playlist->getUserId() == pl->getUserId() && pl->getTitle() == playlist->getTitle()) {
            throw UniqueException("playlist name should be unique");
        }
    }
    int lastId = static_cast<int>(this->playlists.size());
    pl->setId(lastId + 1);
    this->playlists.push_back(pl);
}

vector<Music *> Database::getArtistSongs(int artistId) {
    vector<Music*> result;

    for (auto const &song: this->musics) {
        if (song->getArtist()->getId() == artistId && !song->isDeleted()) {
            result.push_back(song);
        }
    }
    return result;
}

vector<Music*> Database::getMusicsByNameAndArtistAndTag(const string& name, const string& artistName, const string& tagTitle) {
    vector<Music*> result;

    for (auto const &music: this->musics) {
        string musicName = music->getName();
        string artist = music->getArtist()->getUsername();

        if (musicName.find(name) != string::npos && artist.find(artistName) != string::npos) {
            if (tagTitle.empty()) {
                result.push_back(music);
            } else {
                for (Tag* tag: music->getTags()) {
                    if (tag->getTitle() == tagTitle) {
                        result.push_back(music);
                        break;
                    }
                }
            }
        }
    }

    return result;
}

vector<PlayList*> Database::getUserPlayList(int userId) {
    vector <PlayList*> result;

    for (PlayList* pl: this->playlists) {
        if (!pl->isDeleted() && pl->getUserId() == userId) {
            result.push_back(pl);
        }
    }
    return result;
}

void Database::addMusicToPlaylist(Music* music, PlayList* playList) {
    playList->addMusic(music);
}

PlayList* Database::getPlaylistWithId(int playListId) {
    for (PlayList* playlist: playlists) {
        if (playlist->getId() == playListId && !playlist->isDeleted()) {
            return playlist;
        }
    }
    return nullptr;
}

PlayList* Database::getPlaylistWithName(string name) {
    for (PlayList* playlist: playlists) {
        if (playlist->getTitle() == name && !playlist->isDeleted()) {
            return playlist;
        }
    }
    return nullptr;
}

Music* Database::getMusicById(int musicId) {
    for (Music* music: this->musics) {
        if (music->getId() == musicId && !music->isDeleted()) {
            return music;
        }
    }
    return nullptr;
}

int Database::getUserPlaylistCount(BaseUser* user) {
    int count = 0;
    for (PlayList* pl: this->playlists) {
        if (pl->getUserId() == user->getId() && !pl->isDeleted()) {
            count++;
        }
    }
    return count;
}

int Database::getArtistSongsCount(BaseUser* artist) {
    int count = 0;
    for (Music* music: this->getAllMusics()) {
        if (music->getArtist()->getId() == artist->getId()) {
            count++;
        }
    }
    return count;
}

vector<Music*> Database::findManyMusicsByIds(const vector<int> &ids) {
    vector<Music*> result;
    for (int id: ids) {
        for (auto* music: musics) {
            if (music->getId() == id && !music->isDeleted()) {
                result.push_back(music);
                break;
            }
        }
    }
    return result;
}

vector<Music*> Database::getMostLikedMusics(const int &count) {
    int actualCount = std::min(count, static_cast<int>(musics.size()));

    vector<Music*> temp(musics.begin(), musics.end());
    std::sort(
        temp.begin(),
        temp.end(),
        [](Music* m1, Music* m2) {
            return m1->getLikesCount() > m2->getLikesCount();
        }
    );

    return vector<Music*>(temp.begin(), temp.begin() + actualCount);
}
