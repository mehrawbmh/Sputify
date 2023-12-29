#include "../headers/base_user.hpp"

BaseUser::BaseUser(std::string username_, std::string password_) : username(username_), password(password_) {}

bool BaseUser::isDeleted()
{
    return this->deleted;
}
