#include "../headers/base_user.hpp"

BaseUser::BaseUser(std::string username_, std::string password_) : username(username_), password(password_) {}

int BaseUser::getId() {
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
