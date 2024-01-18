#include "../headers/handlers.hpp"
#include "../headers/users_controller.hpp"

using namespace std;

SignupHandler::SignupHandler(Database* _db): db(_db) {}

Response* SignupHandler::callback(Request* req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string mode = req->getBodyParam("mode");

    UsersController controller(this->db);
    return controller.signUp(username, password, mode);
}

LoginHandler::LoginHandler(Database* _db): db(_db) {}

Response* LoginHandler::callback(Request* req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    UsersController controller(this->db);
    return controller.login(username, password);
}

LogoutHandler::LogoutHandler(Database* _db): db(_db) {}

Response* LogoutHandler::callback(Request* req) {
    UsersController control(this->db);
    control.logout();
    
    Response* response = View::redirectResponse("/");
    response->setSessionId("");
    return response;
}

UsersHandler::UsersHandler(Database* _db): db(_db) {}

Response* UsersHandler::callback(Request* req) {
    UsersController control(this->db);
    return control.getAllUsers();
}
