#include "../headers/db.hpp"
#include <stdexcept>
#include <iostream>

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
    int lastId = this->getAllUsers().size();
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

vector<Music *> Database::getAllMusics()
{
    return this->musics;
}

void Database::addMusic(Music *music) {
    int lastId = this->musics.size();
    music->setId(lastId + 1);
    this->musics.push_back(music);
}

void Database::addPlaylist(PlayList* pl) {
    for (PlayList* playlist: playlists) {
        if (playlist->getUserId() == pl->getUserId() && pl->getTitle() == playlist->getTitle()) {
            throw logic_error("playlist name should be unique");
        }
    }
    int lastId = this->playlists.size();
    pl->setId(lastId + 1);
    this->playlists.push_back(pl);
}

vector<Music *> Database::getArtistSongs(int artistId)
{
    vector<Music*> result;

    for (auto const &song: this->musics) {
        if (song->getArtist()->getId() == artistId && !song->isDeleted()) {
            result.push_back(song);
        }
    }
    return result;
}

vector<Music*> Database::getMusicsByNameAndArtistAndTag(string name, string artistName, string tagTitle) {
    vector<Music*> result;

    for (auto const &music: this->musics) {
        string musicName = music->getName();
        string artist = music->getArtist()->getUsername();

        if (musicName.find(name) != string::npos && artist.find(artistName) != string::npos) {
            cout << "GOT here!!\n" << music->getName() << endl;
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

vector<PlayList*> Database::getUserPlayList(int userId)
{
    vector <PlayList*> result;

    for (PlayList* pl: this->playlists) {
        if (pl->getUserId() == userId) {
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
        if (playlist->getId() == playListId) {
            return playlist;
        }
    }
    return nullptr;
}

PlayList* Database::getPlaylistWithName(string name) {
    for (PlayList* playlist: playlists) {
        if (playlist->getTitle() == name) {
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
