#ifndef SPUTIFY_COMMAND_MANAGER_HPP
#define SPUTIFY_COMMAND_MANAGER_HPP

using namespace std;

#include <iostream>
#include <string>
#include "users_controller.hpp"

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
    GET_USERS,
};

const string QUERY_PARAMS_SEPERATOR = "?";
const string SIGNUP_COMMAND = "signup";
const string LOGIN_COMMAND = "login";
const string LOGOUT_COMMAND = "logout";
const string GET_MUSICS_COMMAND = "musics";
const string GET_USERS_COMMAND = "users";

class CommandManager {
private:
    static string findArgValue(vector<string> args, const string &target);
    static void validate(const vector<string> &args);
    static void process(const vector<string> &args, Database* db);
    static HttpMethod getRequestMode(const string &methodInput);
    static Command findCommand(HttpMethod method, const string &route);
    static void mapCommandToController(Command c, const vector<string> &args, Database* db);
    static void handleSignUp(const vector<string> &args, Database* db);
    static void handleLogout(Database *db);
    static void handleLogin(const vector<string> &args, Database* db);

public:
    CommandManager() = default;
    static void handle(Database* db);
};


#endif
