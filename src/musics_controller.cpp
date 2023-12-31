#include "../headers/musics_controller.hpp"
#include "../headers/musics_model.hpp"
#include "../headers/view.hpp"
#include "../headers/client_exception.hpp"

MusicsController::MusicsController(Database *_db) : db(_db) {}

void MusicsController::createMusic(string title, string path, string album, int year, string durationTime, vector<string> tags)
{
    MusicsModel model = MusicsModel(db);
    View view;
    
    int result = model.addNewMusic(title, path, album, year, durationTime, tags);
    cout << view.showResponse(result) << endl;
}

void MusicsController::getOneMusic(int id) {
    MusicsModel model = MusicsModel(db);
    View view;

    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN) << endl;
        return;
    }

    cout << view.showMusicDetail(model.getOneMusic(id)) << endl;
}

void MusicsController::getAllMusics() {
    MusicsModel model = MusicsModel(db);
    View view;

    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN) << endl;
        return;
    }

    cout << view.showMusicsList(model.getAllMusics());
}

void MusicsController::createPlaylist(string name) {
    MusicsModel model(db);
    View view;
    cout << view.showResponse(model.createPlaylist(name)) << endl;
}

void MusicsController::addMusicToPlaylist(int songId, string playlistName) {
    MusicsModel model(db);
    View view;
    cout << view.showResponse(model.addMusicToPlaylist(songId, playlistName)) << endl;
}

void MusicsController::deleteMusic(int songId) {
    MusicsModel model(db);
    View view;
    cout << view.showResponse(model.deleteMusic(songId)) << endl;
}

void MusicsController::getCurrentArtistMusics() {
    MusicsModel model(db);
    View view;
    
    try {
        cout << view.showMusicListDetailed(model.getCurrentArtistMusics());
    } catch(ClientException &exc) {
        cout << view.showResponse(exc.getCode()) << endl;
    }
}

void MusicsController::searchMusic(string name, string artist, string tag) {
    MusicsModel model(db);
    View view;

    try {
        cout << view.showMusicsList(model.searchMusic(name, artist, tag));
    } catch (ClientException &exc) {
        cout << view.showResponse(exc.getCode()) << endl;
    }
}
