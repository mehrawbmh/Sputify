#include "../headers/musics_controller.hpp"

using namespace std;

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
    response->setHeader("Content-Type", "text/html");
    response->setBody(view.showMusicDetail(model.getOneMusic(id)));
    return response;
}

void MusicsController::getAllMusics() {
    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN) << endl;
        return;
    }

    cout << view.showMusicsList(model.getAllMusics());
}

Response* MusicsController::createPlaylist(string name) {
    int status = model.createPlaylist(name);
    Response* response = new Response(status);
    response->setHeader("Content-Type", "application/json");
    
    string message = "[{message: " + view.showResponse(status) + " }";
    message += "{status: " + to_string(status) + " }]";
    
    response->setBody(message);
    return response;
}

void MusicsController::addMusicToPlaylist(int songId, string playlistName) {
    cout << view.showResponse(model.addMusicToPlaylist(songId, playlistName)) << endl;
}

void MusicsController::deleteMusic(const int &songId) {
    cout << view.showResponse(model.deleteMusic(songId)) << endl;
}

void MusicsController::deletePlaylist(const string &playlistName) {
    try {
        model.deletePlaylist(playlistName);
        cout << view.showSuccessResponse() << endl;
    } catch (ClientException &exception) {
        cout << view.showResponse(exception.getCode()) << endl;
    }
}

Response* MusicsController::getCurrentArtistMusics() {
    Response* response = new Response();
    try {
        response->setBody(view.showMusicListDetailed(model.getCurrentArtistMusics()));
        response->setHeader("Content-Type", "text/html");
    } catch (ClientException &exc) {
        response->setStatus(exc.getCode());
        string message(exc.what());
        response->setBody("{message: " + message + "}");
        response->setHeader("Content-Type", "application/json");
    }
    return response;
}

void MusicsController::searchMusic(string name, string artist, string tag) {
    try {
        cout << view.showMusicsList(model.searchMusic(name, artist, tag));
    } catch (ClientException &exc) {
        cout << view.showResponse(exc.getCode()) << endl;
    }
}

void MusicsController::getUserPlaylists(int id) {
    try {
        cout << view.showPlaylists(model.getUserPlaylists(id));
    } catch (ClientException &exception) {
        cout << view.showResponse(exception.getCode()) << endl;
    }
}

void MusicsController::getLikedMusics() {
    try {
        cout << view.showMusicsList(model.getFavoriteMusics());
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

void MusicsController::getPlayList(const int &id, const string &name) {
    try {
        cout << view.showPlaylistDetail(model.getPlayList(id, name), this->db);
    } catch (ClientException &exception) {
        cout << view.showResponse(exception.getCode()) << endl;
    }
}
