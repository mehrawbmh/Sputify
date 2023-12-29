#ifndef SPUTIFY_USER_HPP
#define SPUTIFY_USER_HPP

#include "base_user.hpp"

class User: public BaseUser {
public:
    User(string n, string p);
};

#endif //SPUTIFY_USER_HPP
