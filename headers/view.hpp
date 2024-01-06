#ifndef SPUTIFY_VIEW_HPP
#define SPUTIFY_VIEW_HPP

#include <string>
#include <iostream>
#include <vector>

#include "base_user.hpp"
#include "music.hpp"
#include "play_list.hpp"
#include "artist.hpp"
#include "db.hpp"


using namespace std;

const string RESOPNSE_200_SUCCESS = "OK";
const string RESOPNSE_201_NO_RESOPNSE = "Empty";
const string RESOPNSE_400_BAD_REQUEST = "Bad request";
const string RESPONSE_403_FORBIDDEN = "Permission Denied";
const string RESOPNSE_404_NOT_FOUND = "Not Found";

const int STATUS_200_SUCCESS = 200;
const int STATUS_201_NO_RESOPNSE = 201;
const int STATUS_400_BAD_REQUEST = 400;
const int STATUS_403_FORBIDDEN = 403;
const int STATUS_404_NOT_FOUND = 404;

class View {
private:
    string getMusicDetail(Music* music);

    string getSongsFormatted(int artistId, Database* db);

    string getPlayListsFormatted(int userId, Database* db);
    
    int getPlOrSongsCount(BaseUser* user, Database* db);

public:
    View() = default;

    string showResponse(int statusCode);

    string showSuccessResponse();

    string showUserDetail(BaseUser* user, Database* db);

    string showUsersList(vector<BaseUser*> users, Database* db);

    string showMusicDetail(Music* music);

    string showMusicsList(const vector<Music*>& musics);

    string showMusicListDetailed(const vector<Music*>& musics);

    string showPlaylists(vector<PlayList*> playlists);
};

#endif
