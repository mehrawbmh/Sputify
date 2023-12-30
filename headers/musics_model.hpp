#ifndef SPUTIFY_MUSICS_MODEL_HPP
#define SPUTIFY_MUSICS_MODEL_HPP

#include "db.hpp"

class MusicsModel {
private:
    Database* db;
public:
    MusicsModel(Database* _db);
};

#endif //SPUTIFY_MUSICS_MODEL_HPP