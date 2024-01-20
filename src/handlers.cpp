#include "../headers/handlers.hpp"
#include "../headers/users_controller.hpp"
#include "../headers/musics_controller.hpp"
#include "../utils/strutils.hpp"

#include <unistd.h>
#include <filesystem>

using namespace std;

const string getCurrentDirectory() {
    char cwd[256];
    getcwd(cwd, 256);
    string currentDir(cwd);
    return currentDir + "/";
}

SignupHandler::SignupHandler(Database* _db): db(_db) {}

Response* SignupHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string mode = req->getBodyParam("mode");

    UsersController controller(this->db);
    return controller.signUp(username, password, mode);
}

LoginHandler::LoginHandler(Database* _db): db(_db) {}

Response* LoginHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    UsersController controller(this->db);
    return controller.login(username, password);
}

LogoutHandler::LogoutHandler(Database* _db): db(_db) {}

Response* LogoutHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    control.logout();
    
    Response* response = View::redirectResponse("/");
    response->setSessionId("");
    return response;
}

FollowHandler::FollowHandler(Database* _db): db(_db) {}

Response* FollowHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    string userId = req->getQueryParam("id");
    if (!utils::isNumeric(userId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'user id should be int'}");
        return error;
    }
    return control.follow(stoi(userId));
}

UnfollowHandler::UnfollowHandler(Database* _db): db(_db) {}

Response* UnfollowHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    string userId = req->getQueryParam("id");
    if (!utils::isNumeric(userId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'user id should be int'}");
        return error;
    }
    return control.unfollow(stoi(userId));
}

UsersHandler::UsersHandler(Database* _db): db(_db) {}

Response* UsersHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    return control.getAllUsers();
}

UserDetailHandler::UserDetailHandler(Database* _db): db(_db) {}

Response* UserDetailHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    string userId = req->getQueryParam("id");
    if (!utils::isNumeric(userId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'user id should be int'}");
        return error;
    }
    return control.getOneUser(stoi(userId));
}

MusicDetailHandler::MusicDetailHandler(Database* _db): db(_db) {}

Response* MusicDetailHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    MusicsController control(this->db);
    string musicId = req->getQueryParam("id");

    if (!utils::isNumeric(musicId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'Music id should be int'}");
        return error;
    }
    return control.getOneMusic(stoi(musicId));
}

PlaylistDetailHandler::PlaylistDetailHandler(Database* _db): db(_db) {}

Response* PlaylistDetailHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    MusicsController control(this->db);
    string playlistName = req->getQueryParam("name");

    if (this->db->getCurrentUser() == nullptr) {
        Response* error = new Response(STATUS_403_FORBIDDEN);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 403, 'message': 'You have to login first!'}");
        return error;
    }
    return control.getPlayList(this->db->getCurrentUser()->getId(), playlistName);
}

UploadMusicHandler::UploadMusicHandler(string filePath, Database* _db, Server* _server) : TemplateHandler(filePath), db(_db), server(_server) {}

map<string, string> UploadMusicHandler::handle(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());

    string currentDir = getCurrentDirectory();
    MusicsController controller(this->db);
    map<string, string> context;

    string title = req->getBodyParam("name");
    string path = "static/" + title + DEFAULT_MUSIC_FORMAT;
    string urlPath = "/";
    urlPath += path;
    string album = req->getBodyParam("album");
    string duration = req->getBodyParam("duration");
    string file = req->getBodyParam("file");
    string year = req->getBodyParam("year");
    int musicYear = utils::isNumeric(year) ? stoi(year) : DEFAULT_ALBUM_YEAR;
    
    std::pair result = controller.createMusic(title, path, album, stoi(year), duration, {});

    if (result.first) {
        utils::writeToFile(file, currentDir + path);
        server->get(urlPath, new ShowFile(path, "audio/mp4"));
        context["result"] = TRUE_STR;
    } else {
        context["result"] = FALSE_STR;
    }
    
    context["message"] = result.second;
    return context;
}

ArtistMusicListHandler::ArtistMusicListHandler(Database* _db): db(_db) {}

Response* ArtistMusicListHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    MusicsController control(this->db);
    return control.getCurrentArtistMusics();
}

UserPlaylistsHandler::UserPlaylistsHandler(Database* _db): db(_db) {}

Response* UserPlaylistsHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    if (this->db->getCurrentUser() == nullptr) {
        return new Response(404);
    }

    MusicsController control(this->db);
    return control.getUserPlaylists(db->getCurrentUser()->getId());
}

AddPlaylistHandler::AddPlaylistHandler(Database* _db): db(_db) {}

Response* AddPlaylistHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    MusicsController control(this->db);
    return control.createPlaylist(req->getBodyParam("name"));
}

AddMusicToPlaylistHandlder::AddMusicToPlaylistHandlder(Database* _db): db(_db) {}

Response* AddMusicToPlaylistHandlder::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    MusicsController control(this->db);
    string musicId = req->getQueryParam("musicId");

    if (!utils::isNumeric(musicId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'Music id should be int'}");
        return error;
    }

    return control.addMusicToPlaylist(stoi(musicId), req->getQueryParam("playlistName"));
}