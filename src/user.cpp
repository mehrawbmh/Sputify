#include <utility>

#include "../headers/user.hpp"

User::User(string n, string p): BaseUser(std::move(n), std::move(p)) {}

bool User::canCreatePlayList() {
    return true;
}

bool User::canShareMusic() {
    return false;
}
