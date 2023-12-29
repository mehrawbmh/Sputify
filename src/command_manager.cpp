#include "../headers/command_manager.hpp"
#include "../headers/client_exception.hpp"

HttpMethod CommandManager::getRequestMode(string methodInput) {
    if (methodInput == "POST") {
        return HttpMethod::POST;
    } else if (methodInput == "GET") {
        return HttpMethod::GET;
    } else if (methodInput == "PUT") {
        return HttpMethod::PUT;
    } else if (methodInput == "DELETE") {
        return HttpMethod::DELETE;
    } else {
        throw ClientException(400);
    }
}

void CommandManager::handle(int argc, char* argv[]) {
    string questionMark = argv[3];
    if ((argc < 4) || (questionMark != "?")) {
        throw ClientException(400, "format of request is not valid");
    }

    HttpMethod method = getRequestMode(argv[1]);
    
    if (method == HttpMethod::POST && argv[2] == SIGNUP_COMMAND) {
        if (argc < 8) {
            throw ClientException(400);
        }

        UsersController controller;
        string userName, passWord;
        string firstArg = argv[4];
        string secondArg = argv[6];
        if (firstArg == "username") {
            userName = argv[5];
            if (secondArg == "password") {
                passWord = argv[7];
            } else {
                throw ClientException(400);
            }
        } else if (secondArg == "username") {
            userName = argv[7];
            if (firstArg == "password") {
                passWord = argv[5];
            } else {
                throw ClientException(400);
            }
        } else {
            throw ClientException(400);
        }
        
        return controller.signUp(userName, passWord);
    }

    cout << "INVALID COOMMAND\n";
    throw ClientException(400);
}
