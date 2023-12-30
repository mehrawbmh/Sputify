#ifndef SPUTIFY_USER_HPP
#define SPUTIFY_USER_HPP

#include "base_user.hpp"

class User: public BaseUser {
public:
    User(string n, string p);
    bool canCreatePlayList() override;
    bool canShareMusic() override;
};

#endif //SPUTIFY_USER_HPP
