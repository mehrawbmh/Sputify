#include "../headers/artist.hpp"

Artist::Artist(string n, string p): BaseUser(n, p) {}

bool Artist::canShareMusic() {
    return true;
}

bool Artist::canCreatePlayList() {
    return false;
}
