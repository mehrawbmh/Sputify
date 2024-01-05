#ifndef SPUTIFY_BASE_USER_HPP
#define SPUTIFY_BASE_USER_HPP

#include <string>
#include <vector>

#include "entity.hpp"

using namespace std;

const string MODE_ARTIST = "artist";
const string MODE_NORMAL_USER = "user";

class BaseUser: public Entity {
private:
    int id;
    string username;
    string password; //fixme change to hashed password
    vector<int> followers;
    vector<int> followings;
    vector<int> favoriteMusics;

public:
    BaseUser(string username_, string password_);

    int getId();

    void setId(int id_);

    string getUsername();

    string getPassword();

    vector<int> getFavoriteMusics();

    vector<int> getFollowers();

    vector<int> getFollowings();

    bool addFollower(int userId);

    bool addFollowing(int userId);

    bool removeFollower(int userId);

    bool removeFollowing(int userId);

    virtual bool canShareMusic() = 0;

    virtual bool canCreatePlayList() = 0;
};

#endif //SPUTIFY_BASE_USER_HPP
