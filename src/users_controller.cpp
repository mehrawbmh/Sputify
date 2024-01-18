#include "../headers/users_controller.hpp"
#include "../headers/unique_exception.hpp"
#include "../headers/client_exception.hpp"

#include <string>

UsersController::UsersController(Database* db_): db(db_), model(UsersModel(db_)) {}

Response* UsersController::signUp(const string &userName, const string &passWord, const string &mode) {
    int resultStatus;
    if (mode == MODE_NORMAL_USER) {
        resultStatus = model.addNewUser(userName, passWord);
    } else if (mode == MODE_ARTIST) {
        resultStatus = model.addNewArtist(userName, passWord);
    } else {
        resultStatus = STATUS_400_BAD_REQUEST;
    }

    if (resultStatus == STATUS_200_SUCCESS) {
        Response* resp = View::redirectResponse("/");
        resp->setSessionId(to_string(this->db->getCurrentUser()->getId())); //todo generate safe session and save
        return resp;
    }

    throw Server::Exception("your mode is not valid!");
}

Response* UsersController::login(const string &username, const string &password) {
    int status = this->model.login(username, password);
    if (status == STATUS_200_SUCCESS) {
        Response* resp = View::redirectResponse("/");
        resp->setSessionId(to_string(this->db->getCurrentUser()->getId())); //todo generate safe session and save
        return resp;
    } else {
        Response* res = new Response(status);
        res->setHeader("Content-Type", "application/json");
        res->setBody(view.showResponse(status));
        return res;
    }
}

void UsersController::logout() {
    cout << view.showResponse(this->model.logoutUser()) << endl;
}

Response* UsersController::getOneUser(int id) {
    try {
        Response* response = new Response();
        BaseUser* user = this->model.getOneUser(id);
        response->setBody(view.showUserDetail(user, this->db));
        return response;
    } catch(ClientException &exception) {
        Response* err = new Response(exception.getCode());
        err->setBody(exception.what());
        return err;
    }
    
}

Response* UsersController::getAllUsers() {
    Response* res = new Response;
    try {
        res->setHeader("Content-Type", "text/html");
        res->setBody(view.showUsersList(this->model.getAllUsers(), this->db));
    } catch (ClientException &exc) {
        res->setHeader("Content-Type", "application/json");
        res->setStatus(exc.getCode());
        res->setBody(exc.what());
        cout << "here:" << endl;
        cout << exc.what() << endl;
    }
    return res;
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
