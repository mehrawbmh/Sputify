#include "../headers/musics_controller.hpp"

MusicsController::MusicsController(Database *_db) : db(_db), model(MusicsModel(_db)) {}

void MusicsController::createMusic(string title, string path, string album, int year, string durationTime, vector<string> tags) {
    int result = model.addNewMusic(title, path, album, year, durationTime, tags);
    cout << view.showResponse(result) << endl;
}

void MusicsController::getOneMusic(int id) {
    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN) << endl;
        return;
    }

    cout << view.showMusicDetail(model.getOneMusic(id)) << endl;
}

void MusicsController::getAllMusics() {
    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN) << endl;
        return;
    }

    cout << view.showMusicsList(model.getAllMusics());
}

void MusicsController::createPlaylist(string name) {
    cout << view.showResponse(model.createPlaylist(name)) << endl;
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

void MusicsController::getCurrentArtistMusics() {
    try {
        cout << view.showMusicListDetailed(model.getCurrentArtistMusics());
    } catch(ClientException &exc) {
        cout << view.showResponse(exc.getCode()) << endl;
    }
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

}

void MusicsController::getRecommendedMusics() {

}

void MusicsController::likeMusic(const int &songId) {

}
