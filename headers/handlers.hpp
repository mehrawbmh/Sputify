#ifndef SPUTIFY_HANDLERS_HPP
#define SPUTIFY_HANDLERS_HPP

#include <iostream>
#include <string>

#include "db.hpp"
#include "../server/server.hpp"

class SignupHandler: public RequestHandler {
private:
    Database* db;
public:
    SignupHandler(Database* db);
    Response* callback(Request*);
};

class LoginHandler: public RequestHandler {
private:
    Database* db;
public:
    LoginHandler(Database* db);
    Response* callback(Request*);
};

class LogoutHandler: public RequestHandler {
private:
    Database* db;
public:
    LogoutHandler(Database* db);
    Response* callback(Request*);
};

class FollowHandler: public RequestHandler {
private:
    Database* db;
public:
    FollowHandler(Database* db);
    Response* callback(Request*);
};

class UnfollowHandler: public RequestHandler {
private:
    Database* db;
public:
    UnfollowHandler(Database* db);
    Response* callback(Request*);
};

class UsersHandler: public RequestHandler {
private:
    Database* db;
public:
    UsersHandler(Database* db);
    Response* callback(Request*);
};

class UserDetailHandler: public RequestHandler {
private:
    Database* db;
public:
    UserDetailHandler(Database* db);
    Response* callback(Request*);
};

class MusicDetailHandler: public RequestHandler {
private:
    Database* db;
public:
    MusicDetailHandler(Database* db);
    Response* callback(Request*);
};

class PlaylistDetailHandler: public RequestHandler {
private:
    Database* db;
public:
    PlaylistDetailHandler(Database* db);
    Response* callback(Request*);
};

class UploadMusicHandler: public TemplateHandler {
private:
    Server* server;
    Database* db;
public:
    UploadMusicHandler(string filePath, Database* _db, Server* _server);
    std::map<string, string> handle(Request* req);
};

class HomeHandler: public TemplateHandler {
private:
    Database* db;

public:
    HomeHandler(string filePath, Database* db);
    std::map<string, string> handle(Request* req);
};

class ArtistMusicListHandler: public RequestHandler {
private:
    Database* db;

public:
    ArtistMusicListHandler(Database*);
    Response* callback(Request*);
};

class UserPlaylistsHandler: public RequestHandler {
private:
    Database* db;

public:
    UserPlaylistsHandler(Database*);
    Response* callback(Request*);
};

class AddPlaylistHandler: public RequestHandler {
private:
    Database* db;

public:
    AddPlaylistHandler(Database*);
    Response* callback(Request*);
};

class AddMusicToPlaylistHandlder: public RequestHandler {
private:
    Database* db;

public:
    AddMusicToPlaylistHandlder(Database*);
    Response* callback(Request*);
};

class DeleteMusicHandler: public RequestHandler {
private:
    Database* db;

public:
    DeleteMusicHandler(Database*);
    Response* callback(Request*);
};

class DeletePlaylistHandler: public RequestHandler {
private:
    Database* db;

public:
    DeletePlaylistHandler(Database*);
    Response* callback(Request*);
};

class MusicListHandler: public RequestHandler {
private:
    Database* db;

public:
    MusicListHandler(Database*);
    Response* callback(Request*);
};

#endif // SPUTIFY_HANDLERS_HPP
