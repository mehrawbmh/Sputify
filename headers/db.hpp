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

    vector<BaseUser*> getAllUsers();

    vector<User*> getNormalUsers();

    vector<Artist*> getArtistUsers();

    BaseUser* findOneUserById(const int &id);

    BaseUser* findOneUserByUsername(const string &username);

    void setCurrentUser(BaseUser* user);

    BaseUser* getCurrentUser();

    void addMusic(Music* music);

    vector<Music*> getAllMusics();

    vector<Music*> getArtistSongs(int artistId);

    vector<PlayList*> getUserPlayList(int userId);
};

#endif //SPUTIFY_DB_HPP
