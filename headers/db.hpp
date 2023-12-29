#ifndef SPUTIFY_DB_HPP
#define SPUTIFY_DB_HPP

#include <vector>
#include <string>
#include "user.hpp"
#include "artist.hpp"

using namespace std;

class Database {
private:
    vector<BaseUser*> allUsers;
    vector<User*> normalUsers;
    vector<Artist*> artists;
    BaseUser* currentUser;

public:
    int addNormalUser(User* user);
    
    int addArtist(Artist* artist);

    vector<BaseUser*> getAllUsers();

    vector<User*> getNormalUsers();

    vector<Artist*> getArtistUsers();

    BaseUser* findOneUserById(int id);

    BaseUser* findOneUserByUsername(string username);

    void setCurrentUser(BaseUser* user);
};

#endif