#ifndef SPUTIFY_HANDLERS_HPP
#define SPUTIFY_HANDLERS_HPP

#include <iostream>

#include "db.hpp"
#include "../server/server.hpp"

class SignupHandler: public RequestHandler {
private:
    Database* db;
public:
    SignupHandler(Database* db);
    Response* callback(Request*);
};

class LoginHandler: public RequestHandler {
private:
    Database* db;
public:
    LoginHandler(Database* db);
    Response* callback(Request*);
};

class LogoutHandler: public RequestHandler {
private:
    Database* db;
public:
    LogoutHandler(Database* db);
    Response* callback(Request*);
};

class FollowHandler: public RequestHandler {
private:
    Database* db;
public:
    FollowHandler(Database* db);
    Response* callback(Request*);
};

class UnfollowHandler: public RequestHandler {
private:
    Database* db;
public:
    UnfollowHandler(Database* db);
    Response* callback(Request*);
};

class UsersHandler: public RequestHandler {
private:
    Database* db;
public:
    UsersHandler(Database* db);
    Response* callback(Request*);
};

class UserDetailHandler: public RequestHandler {
private:
    Database* db;
public:
    UserDetailHandler(Database* db);
    Response* callback(Request*);
};

#endif // SPUTIFY_HANDLERS_HPP
