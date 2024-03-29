#ifndef SPUTIFY_MUSICS_CONTROLLER_HPP
#define SPUTIFY_MUSICS_CONTROLLER_HPP

#include "db.hpp"
#include "musics_model.hpp"
#include "utility"
#include "view.hpp"
#include "client_exception.hpp"

using namespace std;

#define DEFAULT_ALBUM_YEAR 2020
#define DEFAULT_MUSIC_FORMAT ".m4a";
#define TRUE_STR "true";
#define FALSE_STR "false";

class MusicsController {
private:
    Database* db;
    MusicsModel model;
    View view;

public:
    MusicsController(Database* db);

    std::pair<bool, string> createMusic(string title, string path, string album, int year, string durationTime, vector<string> tags);

    Response* getOneMusic(int id);

    Response* getAllMusics();

    Response* createPlaylist(string name);

    Response* addMusicToPlaylist(int songId, string playlistName);

    Response* deleteMusic(const int &songId);

    Response* deletePlaylist(const string &playlistName);

    Response* getCurrentArtistMusics();

    void searchMusic(string name, string artist, string tag);

    Response* getUserPlaylists(int id);

    void getLikedMusics();

    void getRecommendedMusics();

    void likeMusic(const int &songId);

    Response* getPlayList(const int &id, const string &name);
};

#endif // SPUTIFY_MUSICS_CONTROLLER_HPP