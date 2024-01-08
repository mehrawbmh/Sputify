#include "../headers/users_controller.hpp"
#include "../headers/unique_exception.hpp"
#include "../headers/client_exception.hpp"


UsersController::UsersController(Database* db_): db(db_), model(UsersModel(db_)) {}

void UsersController::signUp(const string &userName, const string &passWord, const string &mode) {
    int resultStatus;
    if (mode == MODE_NORMAL_USER) {
        resultStatus = model.addNewUser(userName, passWord);
    } else if (mode == MODE_ARTIST) {
        resultStatus = model.addNewArtist(userName, passWord);
    } else {
        resultStatus = STATUS_400_BAD_REQUEST;
    }

    cout << view.showResponse(resultStatus) << endl;
}

void UsersController::login(const string &username, const string &password) {
    cout << view.showResponse(this->model.login(username, password)) << endl;
}

void UsersController::logout() {
    cout << view.showResponse(this->model.logoutUser()) << endl;
}

void UsersController::getOneUser(int id) {
    try {
        BaseUser* user = this->model.getOneUser(id);
        cout << view.showUserDetail(user, this->db);
    } catch(ClientException &exception) {
        cout << view.showResponse(exception.getCode()) << endl;
    }
    
}

void UsersController::getAllUsers() {
    cout << view.showUsersList(this->model.getAllUsers(), this->db);
}

void UsersController::follow(int userId) {
    try {
        this->model.follow(userId);
        cout << view.showSuccessResponse() << endl;
    } catch (UniqueException &uex) {
        cout << view.showResponse(STATUS_400_BAD_REQUEST) << endl;
    } catch(ClientException &cex) {
        cout << view.showResponse(cex.getCode()) << endl;
    }
}

void UsersController::unfollow(int userId) {
    try {
        this->model.unfollow(userId);
        cout << view.showSuccessResponse() << endl;
    } catch (UniqueException &uex) {
        cout << view.showResponse(STATUS_400_BAD_REQUEST) << endl;
    } catch(ClientException &cex) {
        cout << view.showResponse(cex.getCode()) << endl;
    }
}
