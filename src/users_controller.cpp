#include "../headers/users_controller.hpp"

UsersController::UsersController(Database* db) {
    this->model = UsersModel(db);
}

void UsersController::signUp(const string &userName, const string &passWord, const string &mode) {
    int resultStatus;
    if (mode == MODE_NORMAL_USER) {
        cout << "creating normal user...\n";
        resultStatus = model.addNewUser(userName, passWord);
    } else if (mode == MODE_ARTIST) {
        cout << "creating artist...\n";
        resultStatus = model.addNewArtist(userName, passWord);
    } else {
        resultStatus = STATUS_400_BAD_REQUEST;
    }

    cout << view.showResponse(resultStatus) << endl;
}
