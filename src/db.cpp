#include "../headers/db.hpp"

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
