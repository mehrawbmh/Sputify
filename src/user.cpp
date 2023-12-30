#include "../headers/user.hpp"

User::User(string n, string p): BaseUser(n, p) {}

bool canCreatePlayList() {
    return true;
}

bool canShareMusic() {
    return false;
}
