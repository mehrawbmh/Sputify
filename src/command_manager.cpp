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

void CommandManager::handle(int argc, char* argv[], Database* db) {
    string questionMark = argv[3];
    if ((argc < 4) || (questionMark != "?")) {
        throw ClientException(STATUS_400_BAD_REQUEST, "format of request is not valid");
    }

    HttpMethod method = getRequestMode(argv[1]);
    
    if (method == HttpMethod::POST && argv[2] == SIGNUP_COMMAND) {
        if (argc < 9) {
            throw ClientException(STATUS_400_BAD_REQUEST);
        }

        UsersController controller = UsersController(db);
        string userName, passWord;
        string firstArg = argv[4];
        string secondArg = argv[6];
        if (firstArg == "username") {
            userName = argv[5];
            if (secondArg == "password") {
                passWord = argv[7];
            } else {
                throw ClientException(STATUS_400_BAD_REQUEST);
            }
        } else if (secondArg == "username") {
            userName = argv[7];
            if (firstArg == "password") {
                passWord = argv[5];
            } else {
                throw ClientException(STATUS_400_BAD_REQUEST);
            }
        } else {
            throw ClientException(STATUS_400_BAD_REQUEST);
        }
        
        return controller.signUp(userName, passWord, argv[9]); //todo fix this shit of arguments
    }

    cout << "INVALID COOMMAND\n";
    throw ClientException(400);
}
