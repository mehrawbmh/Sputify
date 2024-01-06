#include "../headers/base_user.hpp"
#include <algorithm>

BaseUser::BaseUser(string username_, string password_): Entity(), username(username_), password(password_) {}

int BaseUser::getId() const {
    return this->id;
}

void BaseUser::setId(int id_) {
    this->id = id_;
}

string BaseUser::getUsername() {
    return this->username;
}

string BaseUser::getPassword() {
    return this->password;
}

vector<int> BaseUser::getFavoriteMusics() {
    return this->favoriteMusics;
}

vector<int> BaseUser::getFollowers() {
    return this->followers;
}

vector<int> BaseUser::getFollowings() {
    return this->followings;
}

bool BaseUser::addFollower(int userId) {
    if (userId == id || find(followers.begin(), followers.end(), userId) != followers.end()) {
        return false;
    }

    followers.push_back(userId);
    return true;
}

bool BaseUser::addToFavoriteMusics(const int &songId) {
    if (find(favoriteMusics.begin(), favoriteMusics.end(), songId) == favoriteMusics.end()) {
        favoriteMusics.push_back(songId);
        return true;
    }
    return false;
}

bool BaseUser::addFollowing(int userId) {
    if (userId == id || find(followings.begin(), followings.end(), userId) != followings.end()) {
        return false;
    }

    followings.push_back(userId);
    return true;   
}

bool BaseUser::removeFollower(int userId) {
    auto iterator = find(followers.begin(), followers.end(), userId);

    if (iterator != followers.end()) {
        int index = static_cast<int>(distance(followers.begin(), iterator));
        followers.erase(followers.begin() + index);
        return true;
        
    } else {
        return false;
    }
}

bool BaseUser::removeFollowing(int userId) {
    auto iterator = find(followings.begin(), followings.end(), userId);

    if (iterator != followings.end()) {
        int index = static_cast<int>(distance(followings.begin(), iterator));
        followings.erase(followings.begin() + index);
        return true;

    } else {
        return false;
    }
}
