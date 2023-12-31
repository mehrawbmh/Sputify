#ifndef SPUTIFY_VIEW_HPP
#define SPUTIFY_VIEW_HPP

#include <string>
#include <iostream>
#include <vector>

#include "../headers/base_user.hpp"
#include "../headers/music.hpp"
#include "../headers/artist.hpp"
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

public:
    View() = default;

    string showResponse(int statusCode);

    string showUserDetail(BaseUser* user, Database* db);

    string showUsersList(vector<BaseUser*> users);

    string showMusicDetail(Music* music);

    string showMusicsList(vector<Music*> musics);

    string showMusicListDetailed(vector<Music*> musics);
};

#endif
