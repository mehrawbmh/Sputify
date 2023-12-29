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

    void signUp(string userName, string passWord, string mode);
};

#endif