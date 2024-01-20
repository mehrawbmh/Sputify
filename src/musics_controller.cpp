#include "../headers/musics_controller.hpp"

using namespace std;

#define APPLICATION_JSON_CONTENT "application/json"
#define HTML_TEXT_CONTENT "text/html"

MusicsController::MusicsController(Database *_db) : db(_db), model(MusicsModel(_db)) {}

std::pair<bool, string> MusicsController::createMusic(string title, string path, string album, int year, string durationTime, vector<string> tags) {
    int result = model.addNewMusic(
            std::move(title),
            std::move(path),
            std::move(album),
            std::move(year),
            std::move(durationTime),
            std::move(tags)
    );
    bool success = result == STATUS_200_SUCCESS;
    return std::make_pair(success, view.showResponse(result));
}

Response* MusicsController::getOneMusic(int id) {
    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN) << endl;
        return new Response(STATUS_403_FORBIDDEN);
    }

    Response* response = new Response();
    response->setHeader("Content-Type", HTML_TEXT_CONTENT);
    response->setBody(view.showMusicDetail(model.getOneMusic(id), this->db));
    return response;
}

Response* MusicsController::getAllMusics() {
    if (this->db->getCurrentUser() == nullptr) {
        return new Response(STATUS_403_FORBIDDEN);
    }

    Response* response = new Response();
    response->setHeader("Content-Type", HTML_TEXT_CONTENT);
    response->setBody(view.showMusicsList(model.getAllMusics(), false, ""));
    return response;
}

Response* MusicsController::createPlaylist(string name) {
    int status = model.createPlaylist(name);
    Response* response = new Response(status);
    response->setHeader("Content-Type", APPLICATION_JSON_CONTENT);
    
    string message = "[{message: " + view.showResponse(status) + " }";
    message += "{status: " + to_string(status) + " }]";
    
    response->setBody(message);
    return response;
}

Response* MusicsController::addMusicToPlaylist(int songId, string playlistName) {
    int status = model.addMusicToPlaylist(songId, playlistName);
    Response* response = new Response(status);
    response->setHeader("Content-Type", APPLICATION_JSON_CONTENT);
    
    string message = "[{message: " + view.showResponse(status) + " }";
    message += "{status: " + to_string(status) + " }]";
    
    response->setBody(message);
    return response;
}

Response* MusicsController::deleteMusic(const int &songId) {
    int result = model.deleteMusic(songId);
    if (result == STATUS_200_SUCCESS) {
        return Response::redirect("/");
    }

    Response* response = new Response(result);
    string message = "[{message: " + view.showResponse(result) + " },";
    message += "{code: " + to_string(result) + " }]";
    response->setBody(message);

    return response;
}

Response* MusicsController::deletePlaylist(const string &playlistName) {
    try {
        model.deletePlaylist(playlistName);
        return Response::redirect("/");
    } catch (ClientException &exception) {
        Response* response = new Response(exception.getCode());
        string message(exception.what());
        response->setBody("{message: " + message + "}");
        response->setHeader("Content-Type", APPLICATION_JSON_CONTENT);
        return response;
    }
}

Response* MusicsController::getCurrentArtistMusics() {
    Response* response = new Response();
    try {
        response->setBody(view.showMusicListDetailed(model.getCurrentArtistMusics()));
        response->setHeader("Content-Type", HTML_TEXT_CONTENT);
    } catch (ClientException &exc) {
        response->setStatus(exc.getCode());
        string message(exc.what());
        response->setBody("{message: " + message + "}");
        response->setHeader("Content-Type", APPLICATION_JSON_CONTENT);
    }
    return response;
}

void MusicsController::searchMusic(string name, string artist, string tag) {
    try {
        cout << view.showMusicsList(model.searchMusic(name, artist, tag), false, "");
    } catch (ClientException &exc) {
        cout << view.showResponse(exc.getCode()) << endl;
    }
}

Response* MusicsController::getUserPlaylists(int userId) {
    Response* response = new Response();
    try {
        response->setBody(view.showPlaylists(model.getUserPlaylists(userId)));
        response->setHeader("Content-Type", HTML_TEXT_CONTENT);
    } catch (ClientException &exc) {
        response->setStatus(exc.getCode());
        string message(exc.what());
        response->setBody("{message: " + message + "}");
        response->setHeader("Content-Type", APPLICATION_JSON_CONTENT);
    }
    return response;
}

void MusicsController::getLikedMusics() {
    try {
        cout << view.showMusicsList(model.getFavoriteMusics(), false, "");
    } catch (ClientException &exception) {
        cout << view.showResponse(exception.getCode()) << endl;
    }
}

void MusicsController::getRecommendedMusics() {
    try {
        cout << view.showRecommendedMusics(model.getRecommendedMusics());
    } catch (ClientException &ex) {
        cout << view.showResponse(ex.getCode()) << endl;
    }
}

void MusicsController::likeMusic(const int &songId) {
    try {
        model.likeMusic(songId);
        cout << view.showSuccessResponse() << endl;
    } catch (ClientException &exc) {
        cout << view.showResponse(exc.getCode()) << endl;
    }
}

Response* MusicsController::getPlayList(const int &id, const string &name) {
    Response* response = new Response();
    try {
        response->setBody(view.showPlaylistDetail(model.getPlayList(id, name), this->db));
        response->setHeader("Content-Type", HTML_TEXT_CONTENT);
    } catch (ClientException &exc) {
        response->setStatus(exc.getCode());
        string message(exc.what());
        response->setBody("{message: " + message + "}");
        response->setHeader("Content-Type", APPLICATION_JSON_CONTENT);
    }
    return response;
}
