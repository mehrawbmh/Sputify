#ifndef SPUTIFY_MUSICS_MODEL_HPP
#define SPUTIFY_MUSICS_MODEL_HPP

#include "db.hpp"

const int RECOMMENDED_MUSICS_DEFAULT_COUNT = 5;

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

    vector<Music*> getCurrentArtistMusics();

    vector<Music*> searchMusic(string name, string artist, string tag);

    vector <PlayList*> getUserPlaylists(int userId);

    void deletePlaylist(const string &playlistName);

    PlayList* getPlayList(const int &userId, const string &name);

    void likeMusic(const int &musicId);

    vector<Music*> getFavoriteMusics();

    vector<Music*> getRecommendedMusics();
};

#endif //SPUTIFY_MUSICS_MODEL_HPP