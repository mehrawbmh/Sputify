#ifndef SPUTIFY_MUSICS_MODEL_HPP
#define SPUTIFY_MUSICS_MODEL_HPP

#include "db.hpp"

class MusicsModel {
private:
    Database* db;

public:
    MusicsModel(Database* _db);

    int addNewMusic(string title, string path, string album, int year, string durationTime, vector<string> tags);

    Music* getOneMusic(int id);

    vector<Music*> getAllMusics();

    int createPlaylist(string);

    int addMusicToPlaylist(int songId, string playlistName);

    int deleteMusic(int songId);
};

#endif //SPUTIFY_MUSICS_MODEL_HPP