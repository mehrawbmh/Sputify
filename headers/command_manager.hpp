#ifndef SPUTIFY_COMMAND_MANAGER_HPP
#define SPUTIFY_COMMAND_MANAGER_HPP

using namespace std;

#include <iostream>
#include <string>
#include "users_controller.hpp"

enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE,
};

const string SIGNUP_COMMAND = "signup";

class CommandManager {
private:
    static HttpMethod getRequestMode(string methodInput);

public:
    CommandManager() = default;

    static void handle(int argc, char* argv[], Database* db);
};


#endif