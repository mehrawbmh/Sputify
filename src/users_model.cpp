#include "../headers/users_model.hpp"
#include "../headers/user.hpp"
#include "../headers/artist.hpp"
#include "../headers/client_exception.hpp"

UsersModel::UsersModel(Database* _db): db(_db) {}

int UsersModel::addNewUser(const string &username, const string &pass) {
    cout << "creating new normal user in model...\n" << endl;
    if (this->db->getCurrentUser() != nullptr) {
        return 403;
    }

    if (this->db->findOneUserByUsername(username) != nullptr) {
        return 400;
    }

    User* user = new User(username, pass);    
    this->db->addNormalUser(user);
    this->db->setCurrentUser(user);

    return 200;
}

int UsersModel::addNewArtist(const string &username, const string &pass) {
    cout << "creating new artist in model...\n" << endl;
    if (this->db->getCurrentUser() != nullptr) {
        return 403;
    }

    if (this->db->findOneUserByUsername(username) != nullptr) {
        return 400;
    }

    Artist* artist = new Artist(username, pass);    
    this->db->addArtist(artist);
    this->db->setCurrentUser(artist);
    return 200;
}
