#ifndef SPUTIFY_MUSICS_CONTROLLER_HPP
#define SPUTIFY_MUSICS_CONTROLLER_HPP

#include "db.hpp"

using namespace std;

class MusicsController {
private:
    Database* db;
public:
    MusicsController(Database* db);
};

#endif // SPUTIFY_MUSICS_CONTROLLER_HPP