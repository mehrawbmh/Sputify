#include "../headers/user.hpp"

User::User(string n, string p): BaseUser(n, p) {}

bool User::canCreatePlayList() {
    return true;
}

bool User::canShareMusic() {
    return false;
}
