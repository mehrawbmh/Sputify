#include "../headers/musics_model.hpp"
#include <iostream>

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
