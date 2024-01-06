#ifndef SPUTIFY_DB_HPP
#define SPUTIFY_DB_HPP

#include <vector>
#include <string>

#include "user.hpp"
#include "artist.hpp"
#include "play_list.hpp"
#include "music.hpp"

using namespace std;

class Database {
private:
    BaseUser* currentUser;

    vector<BaseUser*> allUsers;
    vector<User*> normalUsers;
    vector<Artist*> artists;
    vector<Music*> musics;
    vector<PlayList*> playlists;

public:
    int addNormalUser(User* user);
    
    int addArtist(Artist* artist);

    int getUserPlaylistCount(BaseUser*);

    int getArtistSongsCount(BaseUser*);

    vector<BaseUser*> getAllUsers();

    vector<User*> getNormalUsers();

    vector<Artist*> getArtistUsers();

    BaseUser* findOneUserById(const int &id);

    BaseUser* findOneUserByUsername(const string &username);

    vector<BaseUser*> findManyUsersByIds(const vector<int> &ids);

    void setCurrentUser(BaseUser* user);

    BaseUser* getCurrentUser();

    void addMusic(Music* music);

    Music* getMusicById(int musicId);

    void addPlaylist(PlayList* pl);

    PlayList* getPlaylistWithId(int playListId);

    PlayList* getPlaylistWithName(string);

    vector<Music*> getAllMusics(bool excludeDeleted = false);

    vector<Music*> getArtistSongs(int artistId);

    vector<Music*> getMusicsByNameAndArtistAndTag(const string& name, const string& artistName, const string& tagTitle);

    vector<Music*> findManyMusicsByIds(const vector<int> &ids);

    vector<PlayList*> getUserPlayList(int userId);

    void addMusicToPlaylist(Music* music, PlayList* playList);

    vector<Music*> getMostLikedMusics(const int &count);
};

#endif //SPUTIFY_DB_HPP
