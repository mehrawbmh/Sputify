#include "../headers/users_model.hpp"
#include "../headers/client_exception.hpp"

UsersModel::UsersModel(Database* _db): db(_db) {}

int UsersModel::addNewUser(const string &username, const string &pass) {
    if (this->db->getCurrentUser() != nullptr) {
        return 403;
    }

    if (this->db->findOneUserByUsername(username) != nullptr) {
        return 400;
    }

    User* user = new User(username, pass);    
    this->db->addNormalUser(user);
    this->loginUser(user);

    return 200;
}

int UsersModel::addNewArtist(const string &username, const string &pass) {
    if (this->db->getCurrentUser() != nullptr) {
        return 403;
    }

    if (this->db->findOneUserByUsername(username) != nullptr) {
        return 400;
    }

    auto* artist = new Artist(username, pass);
    this->db->addArtist(artist);
    this->loginUser(artist);
    return 200;
}

void UsersModel::loginUser(BaseUser* user) {
    this->db->setCurrentUser(user);
}

int UsersModel::logoutUser() {
    if (this->db->getCurrentUser() == nullptr) {
        return 403;
    }

    this->db->setCurrentUser(nullptr);
    return 200;
}

int UsersModel::login(const string &username, const string &password) {
    if (this->db->getCurrentUser() != nullptr) {
        return 403;
    }

    for (const auto &user: this->db->getAllUsers()) {
        if (user->getUsername() == username) {
            if (user->getPassword() != password) {
                return 403;
            }
            this->loginUser(user);
            return 200;
        }
    }

    return 404;
}

BaseUser* UsersModel::getOneUser(int id) {
    if (this->db->getCurrentUser() == nullptr) {
        throw ClientException(403, "you are not logged in yet!\n");
    }

    auto allUsers = this->db->getAllUsers();
    for (const auto user: allUsers) {
        if (user->getId() == id && !user->isDeleted()) {
            return user;
        }
    }

    return nullptr;
}

vector<BaseUser*> UsersModel::getAllUsers() {
    if (this->db->getCurrentUser() == nullptr) {
        throw ClientException(403, "you are not logged in yet!\n");
    }

    vector<BaseUser*> result;
    for (const auto user: this->db->getAllUsers()) {
        if (!user->isDeleted()) {
            result.push_back(user);
        }
    }

    return result;
}
