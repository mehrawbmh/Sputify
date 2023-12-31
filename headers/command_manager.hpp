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
    static string findArgValue(vector<string> args, const string &target);
    static Command findCommand(HttpMethod method, const string &route, int argsCount);
    static HttpMethod getRequestMode(const string &methodInput);

    static void validate(const vector<string> &args);
    static void process(const vector<string> &args, Database* db);
    static void mapCommandToController(Command c, const vector<string> &args, Database* db);

    static void handleSignUp(const vector<string> &args, Database* db);
    static void handleLogout(Database *db);
    static void handleLogin(const vector<string> &args, Database* db);
    static void handleGetSingleUser(const vector<string> &args, Database* db);
    static void handleGetManyUsers(const vector<string> &args, Database* db);
    
    static void handleAddPlayList(const vector<string> &args, Database* db);
    static void handleGetManyPlayLists(const vector<string> &args, Database* db);
    static void handleAddSongToPlayList(const vector<string> &args, Database *db);
    
    static void handleGetManyMusics(const vector<string> &args, Database* db);
    static void handleAddMusic(const vector<string> &args, Database* db);
    static void handleDeleteMusic(const vector<string> &args, Database* db);
    static void handleGetOneMusic(const vector<string> &args, Database* db);
    static void handleSearchMusic(const vector<string> &args, Database* db);

public:
    CommandManager() = default;
    static void handle(Database* db);
};


#endif
