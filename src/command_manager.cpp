#include "../headers/command_manager.hpp"
#include "../headers/client_exception.hpp"

#include <istream>
#include <iostream>
#include <sstream>


HttpMethod CommandManager::getRequestMode(const string &methodInput) {
    if (methodInput == "POST") {
        return HttpMethod::POST;
    } else if (methodInput == "GET") {
        return HttpMethod::GET;
    } else if (methodInput == "PUT") {
        return HttpMethod::PUT;
    } else if (methodInput == "DELETE") {
        return HttpMethod::DELETE;
    } else {
        throw ClientException(STATUS_400_BAD_REQUEST);
    }
}

string CommandManager::findArgValue(vector<string> args, const string &target) {
    string result = "";
    for (int i = 0; i < args.size() - 1; i++) {
        if (args[i] == target) {
            if (!args[i+1].starts_with("<")) {
                throw ClientException(STATUS_400_BAD_REQUEST, "parameter value should be inside < >");
            }
            for (int j = i+1; j < args.size(); j++) {
                result = result + args[j] + " ";
                if (args[j].ends_with(">")) {
                    break;
                }
            }
            break;
        }
    }
    return result.substr(1, result.size()-3);
}

void CommandManager::validate(const vector<string> &args) {
    if (args.size() < 3 || args[2] != QUERY_PARAMS_SEPERATOR) {
        throw ClientException(STATUS_400_BAD_REQUEST, "format of request is not valid");
    }
}

Command CommandManager::findCommand(HttpMethod method, const string &route) {
    if (method == HttpMethod::POST && route == SIGNUP_COMMAND) {
        return Command::SIGNUP;
    } else if (method == HttpMethod::POST && route == LOGOUT_COMMAND) {
        return Command::LOGOUT;
    }

    throw ClientException(STATUS_404_NOT_FOUND, "Invalid command provided");
}

void CommandManager::handleSignUp(const vector<string> &args, Database* db) {
    UsersController controller = UsersController(db);
    string username = findArgValue(args, "username");
    string password = findArgValue(args, "password");
    string mode = findArgValue(args, "mode");

    if (username.empty() || password.empty() || mode.empty()) {
        cout << "empty!!\n";
        throw ClientException(STATUS_400_BAD_REQUEST, "insufficient request params for signup");
    }
    cout << "passed arg conditions!\n";
    return controller.signUp(username, password, mode);
}

void CommandManager::mapCommandToController(Command c, const vector<string> &args, Database* db) {
    switch (c) {
    case Command::SIGNUP: {
        cout << "handling signup...\n";
        return handleSignUp(args, db);
    }
    default:
        cout << "GOING TO DEFAULT\n";
        break;
    }
}

void CommandManager::process(const vector<string> &args, Database* db) {
    HttpMethod method = getRequestMode(args[0]);
    Command command = findCommand(method, args[1]);
    mapCommandToController(command, args, db);
}

void CommandManager::handle(Database* db) {
    string line;
    while (getline(cin, line)) {
        vector<string> args;
        string word;
        istringstream ss(line);
        while (getline(ss, word, ' ')) {
            // if (word.empty()) continue;
            args.push_back(word);
        }

        try {
            cout <<"validating...\n";
            validate(args);
            cout << "processing...\n";
            process(args, db);
        } catch(ClientException &exc) {
            cout << "handling error...\n";
            View view;
            cout << exc.what();
            cout << view.showResponse(exc.getCode()) << endl;
        }
    }
}
