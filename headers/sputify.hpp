#ifndef SPUTIFY_SPUTIFY_HPP
#define SPUTIFY_SPUTIFY_HPP

#include "../server/server.hpp"
#include "handlers.hpp"
#include "db.hpp"

#define DEFAULT_PORT 8000;

class Sputify {
private:
    Database* db;

public:
    Sputify(Database* database);
    void run(int argc, char* argv[]);
    void mapRoutes(Server& server);
};


#endif //SPUTIFY_SPUTIFY_HPP