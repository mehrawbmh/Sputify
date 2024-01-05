#ifndef SPUTIFY_USERS_CONTROLLER_HPP
#define SPUTIFY_USERS_CONTROLLER_HPP

#include <string>

#include "users_model.hpp"
#include "view.hpp"
#include "client_exception.hpp"

using namespace std;

class UsersController {
private:
    UsersModel model;
    View view;
    Database *db;

public:
    UsersController(Database* db);

    void signUp(const string &userName, const string &passWord, const string &mode);

    void logout();

    void login(const string &username, const string &password);

    void getOneUser(int id);

    void getAllUsers();

    void follow(int userId);

    void unfollow(int userId);
};

#endif