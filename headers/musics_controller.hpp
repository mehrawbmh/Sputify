#ifndef SPUTIFY_MUSICS_CONTROLLER_HPP
#define SPUTIFY_MUSICS_CONTROLLER_HPP

#include "db.hpp"

using namespace std;

class MusicsController {
private:
    Database* db;
public:
    MusicsController(Database* db);

    void createMusic(string title, string path, string album, int year, string durationTime, vector<string> tags);

    void getOneMusic(int id);

    void getAllMusics();
};

#endif // SPUTIFY_MUSICS_CONTROLLER_HPP