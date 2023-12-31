#include "../headers/musics_controller.hpp"
#include "../headers/musics_model.hpp"
#include "../headers/view.hpp"

MusicsController::MusicsController(Database *_db) : db(_db) {}

void MusicsController::createMusic(string title, string path, string album, int year, string durationTime, vector<string> tags)
{
    MusicsModel model = MusicsModel(db);
    View view;
    
    cout << "here before model\n";
    int result = model.addNewMusic(title, path, album, year, durationTime, tags);
    cout << view.showResponse(result) << endl;
}

void MusicsController::getOneMusic(int id) {
    MusicsModel model = MusicsModel(db);
    View view;

    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN);
    }

    cout << "getting one music...\n";
    cout << view.showMusicDetail(model.getOneMusic(id)) << endl;
}

void MusicsController::getAllMusics() {
    MusicsModel model = MusicsModel(db);
    View view;

    if (this->db->getCurrentUser() == nullptr) {
        cout << view.showResponse(STATUS_403_FORBIDDEN);
        return;
    }

    cout << "getting all musics...\n";
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