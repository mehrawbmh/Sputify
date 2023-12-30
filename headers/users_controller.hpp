#ifndef SPUTIFY_USERS_CONTROLLER_HPP
#define SPUTIFY_USERS_CONTROLLER_HPP

#include <string>
#include "users_model.hpp"
#include "view.hpp"

using namespace std;

class UsersController {
private:
    UsersModel model;
    View view;

public:
    UsersController(Database* db);

    void signUp(const string &userName, const string &passWord, const string &mode);

    void logout();

    void login(const string &username, const string &password);
};

#endif