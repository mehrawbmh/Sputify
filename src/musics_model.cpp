#include "../headers/musics_model.hpp"
#include "../headers/play_list.hpp"

#include <iostream>
#include <stdexcept>
#include "../headers/client_exception.hpp"

using namespace std;

MusicsModel::MusicsModel(Database* _db): db(_db) {}


int MusicsModel::addNewMusic(string title, string path, string album, int year, string durationTime, vector<string> tags) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canShareMusic()) {
        return 403;
    }

    Music* music = new Music(dynamic_cast<Artist*>(this->db->getCurrentUser()), title, path, durationTime, year, album);
    for (auto const tagTitle: tags) {
        music->addTag(new Tag(tagTitle)); // todo better way later
    }
    
    this->db->addMusic(music);
    return 200;
}

Music* MusicsModel::getOneMusic(int id) {
    for (Music* music: this->db->getAllMusics()) {
        if ((music->getId() == id) && (!music->isDeleted())) {
            cout << "found\n";
            return music;
        }
    }
    cout << "nothing found!\n";
    return nullptr;
}

vector<Music*> MusicsModel::getAllMusics() {
    vector<Music*> result;
    for (Music* music: this->db->getAllMusics()) {
        if (!music->isDeleted()) {
            result.push_back(music);
        }
    }

    return result;
}

int MusicsModel::createPlaylist(string title) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canCreatePlayList()) {
        return 403;
    }

    try {
        this->db->addPlaylist(new PlayList(title, this->db->getCurrentUser()->getId()));
    } catch (logic_error &err) {
        return 400;
    }
    return 200;
}

int MusicsModel::addMusicToPlaylist(int songId, string playlistName) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canCreatePlayList()) {
        return 403;
    }

    Music* music = this->db->getMusicById(songId);
    if (music == nullptr) {
        return 404;
    }

    PlayList* pl = this->db->getPlaylistWithName(playlistName);
    if (pl == nullptr) {
        return 404;
    }

    //todo check duplicate music in PL
    this->db->addMusicToPlaylist(music, pl);
    return 200;
}

int MusicsModel::deleteMusic(int songId) {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canShareMusic()) {
        return 403;
    }

    Music* music = this->db->getMusicById(songId);
    if (music == nullptr || music->isDeleted()) {
        return 404;
    }
    
    if (music->getArtist()->getId() != this->db->getCurrentUser()->getId()) {
        return 403;
    }

    music->setAsDeleted();
    // todo: remove from playlists!
    return 200;
}

vector<Music*> MusicsModel::getCurrentArtistMusics() {
    if (this->db->getCurrentUser() == nullptr || !this->db->getCurrentUser()->canShareMusic()) {
        throw ClientException(403, "you have to log in as an artist!");
    }

    return this->db->getArtistSongs(this->db->getCurrentUser()->getId());
}
