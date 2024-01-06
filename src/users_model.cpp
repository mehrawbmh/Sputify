#include "../headers/users_model.hpp"
#include "../headers/client_exception.hpp"
#include "../headers/unique_exception.hpp"
#include "../headers/view.hpp"

UsersModel::UsersModel(Database* _db): db(_db) {}

int UsersModel::addNewUser(const string &username, const string &pass) {
    if (this->db->getCurrentUser() != nullptr) {
        return STATUS_403_FORBIDDEN;
    }

    if (this->db->findOneUserByUsername(username) != nullptr) {
        return STATUS_400_BAD_REQUEST;
    }

    User* user = new User(username, pass);    
    this->db->addNormalUser(user);
    this->loginUser(user);

    return STATUS_200_SUCCESS;
}

int UsersModel::addNewArtist(const string &username, const string &pass) {
    if (this->db->getCurrentUser() != nullptr) {
        return STATUS_403_FORBIDDEN;
    }

    if (this->db->findOneUserByUsername(username) != nullptr) {
        return STATUS_400_BAD_REQUEST;
    }

    auto* artist = new Artist(username, pass);
    this->db->addArtist(artist);
    this->loginUser(artist);

    return STATUS_200_SUCCESS;
}

void UsersModel::loginUser(BaseUser* user) {
    this->db->setCurrentUser(user);
}

int UsersModel::logoutUser() {
    if (this->db->getCurrentUser() == nullptr) {
        return STATUS_403_FORBIDDEN;
    }

    this->db->setCurrentUser(nullptr);
    return STATUS_200_SUCCESS;
}

int UsersModel::login(const string &username, const string &password) {
    if (this->db->getCurrentUser() != nullptr) {
        return STATUS_403_FORBIDDEN;
    }

    for (const auto &user: this->db->getAllUsers()) {
        if (user->getUsername() == username) {
            if (user->getPassword() != password) {
                return STATUS_403_FORBIDDEN;
            }
            this->loginUser(user);
            return STATUS_200_SUCCESS;
        }
    }

    return STATUS_404_NOT_FOUND;
}

BaseUser* UsersModel::getOneUser(int id) {
    if (this->db->getCurrentUser() == nullptr) {
        throw ClientException(STATUS_403_FORBIDDEN, "you are not logged in yet!\n");
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
        throw ClientException(STATUS_403_FORBIDDEN, "you are not logged in yet!\n");
    }

    vector<BaseUser*> result;
    for (const auto user: this->db->getAllUsers()) {
        if (!user->isDeleted()) {
            result.push_back(user);
        }
    }

    return result;
}

void UsersModel::follow(int userId) {
    auto *current = this->db->getCurrentUser();
    auto *other = this->db->findOneUserById(userId);

    if (!current) {
        throw ClientException(STATUS_403_FORBIDDEN, "you have to login first");
    }

    if (!other) {
        throw ClientException(STATUS_404_NOT_FOUND, "user not found");
    }

    if (current->getId() == other->getId()) {
        throw ClientException(STATUS_400_BAD_REQUEST, "you can't follow yourself!");
    }

    if (!current->addFollowing(other->getId()) || !other->addFollower(current->getId())) {
        throw UniqueException("already followed!");
    }
}

void UsersModel::unfollow(int userId) {
    auto *current = this->db->getCurrentUser();
    auto *other = this->db->findOneUserById(userId);

    if (!current) {
        throw ClientException(STATUS_403_FORBIDDEN, "you have to login first");
    }

    if (!other) {
        throw ClientException(STATUS_404_NOT_FOUND, "user not found");
    }

    if (current->getId() == other->getId()) {
        throw ClientException(STATUS_400_BAD_REQUEST, "you can't unfollow yourself!");
    }

    if (!current->removeFollowing(other->getId()) || !other->removeFollower(current->getId())) {
        throw UniqueException("User was not followed!");
    }
}
