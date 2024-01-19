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

    void getOneMusic(int id);

    void getAllMusics();

    void createPlaylist(string name);

    void addMusicToPlaylist(int songId, string playlistName);

    void deleteMusic(const int &songId);

    void deletePlaylist(const string &playlistName);

    void getCurrentArtistMusics();

    void searchMusic(string name, string artist, string tag);

    void getUserPlaylists(int id);

    void getLikedMusics();

    void getRecommendedMusics();

    void likeMusic(const int &songId);

    void getPlayList(const int &id, const string &name);
};

#endif // SPUTIFY_MUSICS_CONTROLLER_HPP