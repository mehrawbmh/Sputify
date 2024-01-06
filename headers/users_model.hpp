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
    
    void loginUser(BaseUser* user);

public:
    UsersModel(Database*);

    UsersModel() = default;

    int addNewUser(const string &user, const string &pass);

    int addNewArtist(const string &user, const string &pass);

    int logoutUser();

    int login(const string &username, const string &password);

    BaseUser* getOneUser(int id);

    vector<BaseUser*> getAllUsers();

    void follow(int userId);

    void unfollow(int userId);
};

#endif
