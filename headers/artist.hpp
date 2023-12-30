#ifndef SPUTIFY_ARTIST_HPP
#define SPUTIFY_ARTIST_HPP

#include "base_user.hpp"

class Artist: public BaseUser {
public:
    Artist(string n, string p);
    bool canCreatePlayList() override;
    bool canShareMusic() override;
};

#endif //SPUTIFY_ARTIST_HPP
