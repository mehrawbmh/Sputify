#ifndef SPUTIFY_BASE_USER_HPP
#define SPUTIFY_BASE_USER_HPP

#include <string>

using namespace std;

class BaseUser {
private:
    bool deleted = false;
protected:
    string username;
    string password; //fixme change to hashed password
public:
    BaseUser(string username_, string password_);
    bool isDeleted();
};

#endif //SPUTIFY_BASE_USER_HPP
