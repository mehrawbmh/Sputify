#include "../headers/base_user.hpp"

BaseUser::BaseUser(std::string username_, std::string password_) : username(username_), password(password_) {}

bool BaseUser::isDeleted()
{
    return this->deleted;
}

int BaseUser::getId()
{
    return this->id;
}

void BaseUser::setId(int id_)
{
    this->id = id_;
}

void BaseUser::setAsDeleted() {
    this->deleted = true;
}

string BaseUser::getUsername() {
    return this->username;
}

string BaseUser::getPassword() {
    return this->password;
}
