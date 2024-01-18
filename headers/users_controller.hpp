#ifndef SPUTIFY_USERS_CONTROLLER_HPP
#define SPUTIFY_USERS_CONTROLLER_HPP

#include <string>

#include "users_model.hpp"
#include "view.hpp"
#include "client_exception.hpp"
#include "../server/server.hpp"

using namespace std;

class UsersController {
private:
    UsersModel model;
    View view;
    Database *db;

public:
    UsersController(Database* db);

    Response* signUp(const string &userName, const string &passWord, const string &mode);

    void logout();

    Response* login(const string &username, const string &password);

    Response* getOneUser(int id);

    Response* getAllUsers();

    void follow(int userId);

    void unfollow(int userId);
};

#endif
