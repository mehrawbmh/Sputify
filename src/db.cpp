#include "../headers/db.hpp"

int Database::addNormalUser(User *user) {
    int lastId = this->getAllUsers().size();
    user->setId(lastId + 1);

    this->allUsers.push_back(user);
    this->normalUsers.push_back(user);

    return 200;
}

void Database::setCurrentUser(BaseUser* user) {
    this->currentUser = user;
}

int Database::addArtist(Artist *artist) {
    int lastId = this->getAllUsers().size();
    artist->setId(lastId + 1);

    this->allUsers.push_back(artist);
    this->artists.push_back(artist);
    
    return 200;
}

vector<BaseUser*> Database::getAllUsers() {
    return this->allUsers;
}

vector<User*> Database::getNormalUsers() {
    return this->normalUsers;
}

vector<Artist*> Database::getArtistUsers() {
    return this->artists;
}

BaseUser* Database::findOneUserById(const int &id) {
    for (auto baseUser: allUsers) {
        if (baseUser->getId() == id) {
            return baseUser;
        }
    }
    return nullptr;
}

BaseUser* Database::findOneUserByUsername(const string &username) {
    for (auto baseUser: allUsers) {
        if (baseUser->getUsername() == username) {
            return baseUser;
        }
    }
    return nullptr;
}

