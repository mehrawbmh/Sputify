#ifndef SPUTIFY_BASE_USER_HPP
#define SPUTIFY_BASE_USER_HPP

#include <string>

using namespace std;

const string MODE_ARTIST = "artist";
const string MODE_NORMAL_USER = "user";

class BaseUser {
private:
    bool deleted = false;
protected:
    int id;
    string username;
    string password; //fixme change to hashed password
public:
    BaseUser(string username_, string password_);
    
    bool isDeleted();

    void setAsDeleted();

    int getId();

    void setId(int id_);

    string getUsername();

    string getPassword();
};

#endif //SPUTIFY_BASE_USER_HPP
