#include "../headers/handlers.hpp"
#include "../headers/users_controller.hpp"

#include "../utils/strutils.hpp"

using namespace std;

SignupHandler::SignupHandler(Database* _db): db(_db) {}

Response* SignupHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string mode = req->getBodyParam("mode");

    UsersController controller(this->db);
    return controller.signUp(username, password, mode);
}

LoginHandler::LoginHandler(Database* _db): db(_db) {}

Response* LoginHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    UsersController controller(this->db);
    return controller.login(username, password);
}

LogoutHandler::LogoutHandler(Database* _db): db(_db) {}

Response* LogoutHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    control.logout();
    
    Response* response = View::redirectResponse("/");
    response->setSessionId("");
    return response;
}

FollowHandler::FollowHandler(Database* _db): db(_db) {}

Response* FollowHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    string userId = req->getQueryParam("id");
    if (!utils::isNumeric(userId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'user id should be int'}");
        return error;
    }
    return control.follow(stoi(userId));
}

UnfollowHandler::UnfollowHandler(Database* _db): db(_db) {}

Response* UnfollowHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    string userId = req->getQueryParam("id");
    if (!utils::isNumeric(userId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'user id should be int'}");
        return error;
    }
    return control.unfollow(stoi(userId));
}

UsersHandler::UsersHandler(Database* _db): db(_db) {}

Response* UsersHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    return control.getAllUsers();
}

UserDetailHandler::UserDetailHandler(Database* _db): db(_db) {}

Response* UserDetailHandler::callback(Request* req) {
    this->db->handleCurrentUserBySession(req->getSessionId());
    UsersController control(this->db);
    string userId = req->getQueryParam("id");
    if (!utils::isNumeric(userId)) {
        Response* error = new Response(STATUS_400_BAD_REQUEST);
        error->setHeader("Content-Type", "application/json");
        error->setBody("{'status': 400, 'message': 'user id should be int'}");
        return error;
    }
    return control.getOneUser(stoi(userId));
}
