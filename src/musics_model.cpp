#include "../headers/musics_model.hpp"
#include "../headers/play_list.hpp"

#include <iostream>
#include <stdexcept>
#include "../headers/client_exception.hpp"
#include "../headers/view.hpp"

using namespace std;

MusicsModel::MusicsModel(Database* _db): db(_db) {}


int MusicsModel::addNewMusic(string title, string path, string album, int year, string durationTime, vector<string> tags) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canShareMusic()) {
        return STATUS_403_FORBIDDEN;
    }

    Music* music = new Music(dynamic_cast<Artist*>(this->db->getCurrentUser()), title, path, durationTime, year, album);
    for (auto const tagTitle: tags) {
        music->addTag(new Tag(tagTitle)); // todo better way later
    }
    
    this->db->addMusic(music);
    return STATUS_200_SUCCESS;
}

Music* MusicsModel::getOneMusic(int id) {
    for (Music* music: this->db->getAllMusics()) {
        if ((music->getId() == id) && (!music->isDeleted())) {
            return music;
        }
    }

    return nullptr;
}

vector<Music*> MusicsModel::getAllMusics() {
    return this->db->getAllMusics(true);
}

int MusicsModel::createPlaylist(string title) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canCreatePlayList()) {
        return STATUS_403_FORBIDDEN;
    }

    try {
        this->db->addPlaylist(new PlayList(title, this->db->getCurrentUser()->getId()));
    } catch (logic_error &err) {
        return STATUS_400_BAD_REQUEST;
    }

    return STATUS_200_SUCCESS;
}

int MusicsModel::addMusicToPlaylist(int songId, string playlistName) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canCreatePlayList()) {
        return STATUS_403_FORBIDDEN;
    }

    Music* music = this->db->getMusicById(songId);
    if (music == nullptr) {
        return STATUS_404_NOT_FOUND;
    }

    PlayList* pl = this->db->getPlaylistWithName(playlistName);
    if (pl == nullptr) {
        return STATUS_404_NOT_FOUND;
    }

    //todo check duplicate music in PL
    this->db->addMusicToPlaylist(music, pl);
    return STATUS_200_SUCCESS;
}

int MusicsModel::deleteMusic(int songId) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canShareMusic()) {
        return STATUS_403_FORBIDDEN;
    }

    Music* music = this->db->getMusicById(songId);
    if (music == nullptr || music->isDeleted()) {
        return STATUS_404_NOT_FOUND;
    }
    
    if (music->getArtist()->getId() != this->db->getCurrentUser()->getId()) {
        return STATUS_403_FORBIDDEN;
    }

    music->markAsDeleted();
    // todo: remove from playlists!
    return STATUS_200_SUCCESS;
}

void MusicsModel::deletePlaylist(const string &playlistName) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canCreatePlayList()) {
        throw ClientException(STATUS_403_FORBIDDEN, "you have to log in as a normal user!");
    }

    PlayList* playlist = this->db->getPlaylistWithName(playlistName);
    if (playlist == nullptr) {
        throw ClientException(STATUS_404_NOT_FOUND, "playlist not found!");
    }

    for (PlayList* pl: this->db->getUserPlayList(this->db->getCurrentUser()->getId())) {
        if (pl->getId() == playlist->getId()) {
            playlist->markAsDeleted();
            return;
        }
    }

    throw ClientException(STATUS_403_FORBIDDEN, "you can't delete other user's playlists!");
}

vector<Music*> MusicsModel::getCurrentArtistMusics() {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canShareMusic()) {
        throw ClientException(STATUS_403_FORBIDDEN, "you have to log in as an artist!");
    }

    return this->db->getArtistSongs(this->db->getCurrentUser()->getId());
}

vector<Music*> MusicsModel::searchMusic(string name, string artist, string tag) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canCreatePlayList()) {
        throw ClientException(STATUS_403_FORBIDDEN, "you have to log in as an artist!");
    }

    return this->db->getMusicsByNameAndArtistAndTag(name, artist, tag);
}

vector <PlayList*> MusicsModel::getUserPlaylists(int userId) {
    BaseUser* user = this->db->findOneUserById(userId);

    if (this->db->getCurrentUser() == nullptr || this->db->getCurrentUser()->canShareMusic()) {
        throw ClientException(STATUS_403_FORBIDDEN, "you do not have access to this page");
    }

    if (user == nullptr)  {
        throw ClientException(STATUS_404_NOT_FOUND, "user not found");
    }

    if (user->canShareMusic()) {
        throw ClientException(STATUS_400_BAD_REQUEST, "you can not get an artist\'s playlist!");
    }

    return this->db->getUserPlayList(userId);
}
