#ifndef SPUTIFY_COMMAND_MANAGER_HPP
#define SPUTIFY_COMMAND_MANAGER_HPP

using namespace std;

#include <iostream>
#include <string>
#include "users_controller.hpp"
#include "musics_controller.hpp"

enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE,
};

enum class Command {
    SIGNUP,
    LOGIN,
    LOGOUT,
    GET_MUSICS,
    GET_ARTIST_MUSICS,
    GET_MUSIC,
    SEARCH_MUSIC,
    CREATE_MUSIC,
    DELETE_MUSIC,
    ADD_MUSIC_TO_PLAY_LIST,
    ADD_PLAY_LIST,
    GET_PLAY_LIST,
    GET_USER,
    GET_USERS,
};

const string QUERY_PARAMS_SEPERATOR = "?";
const string SIGNUP_COMMAND = "signup";
const string LOGIN_COMMAND = "login";
const string LOGOUT_COMMAND = "logout";
const string GET_MUSICS_COMMAND = "musics";
const string ONE_MUSIC_COMMAND = "music";
const string GET_USER_COMMAND = "users";
const string SEARCH_MUSIC_COMMAND = "search_music";
const string GET_ARTIST_MUSICS_COMMAND = "registered_musics";
const string PLAYLIST_ACTIONS_COMMAND = "playlist";
const string ADD_MUSIC_TO_PLAYLIST_COMMAND = "add_playlist";

class CommandManager {
private:    
    Database* db;
    MusicsController musicsController;
    UsersController usersController;


    string findArgValue(vector<string> args, const string &target);
    Command findCommand(HttpMethod method, const string &route, int argsCount);
    HttpMethod getRequestMode(const string &methodInput);
    void validate(const vector<string> &args);
    void process(const vector<string> &args);
    void mapCommandToController(Command c, const vector<string> &args);
    void handleSignUp(const vector<string> &args);
    void handleLogout();
    void handleLogin(const vector<string> &args);
    void handleGetSingleUser(const vector<string> &args);
    void handleGetManyUsers(const vector<string> &args);
    void handleAddPlayList(const vector<string> &args);
    void handleGetArtistMusics(const vector<string> &args);
    void handleGetManyPlayLists(const vector<string> &args);
    void handleAddSongToPlayList(const vector<string> &args);
    void handleGetManyMusics(const vector<string> &args);
    void handleAddMusic(const vector<string> &args);
    void handleDeleteMusic(const vector<string> &args);
    void handleGetOneMusic(const vector<string> &args);
    void handleSearchMusic(const vector<string> &args);

public:    
    CommandManager(Database* db);
    void handle();
};


#endif
