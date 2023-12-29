#ifndef SPUTIFY_USERS_MODEL_HPP
#define SPUTIFY_USERS_MODEL_HPP

#include <string>
#include <iostream>
#include "db.hpp"
#include "base_user.hpp"

using namespace std;

class UsersModel {
private:
    Database* db;
public:
    UsersModel(Database*);
    UsersModel() = default;

    int addNewUser(const string &user, const string &pass);

    int addNewArtist(const string &user, const string &pass);
};

#endif
