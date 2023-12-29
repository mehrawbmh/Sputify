#ifndef SPUTIFY_USERS_MODEL_HPP
#define SPUTIFY_USERS_MODEL_HPP

#include <string>
#include <iostream>

using namespace std;

class UsersModel {
public:
    UsersModel();
    int addNewUser(string user, string pass);
};

#endif
