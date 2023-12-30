#include "../headers/artist.hpp"

Artist::Artist(string n, string p): BaseUser(n, p) {}

bool canShareMusic() {
    return true;
}

bool canCreatePlayList() {
    return false;
}
