#include "../headers/command_manager.hpp"
#include "../headers/client_exception.hpp"

#include <istream>
#include <iostream>
#include <sstream>

bool is_number(const string &s) {
  return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

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

    return result.size() < 4 ? "" : result.substr(1, result.size() - 3);
}

void CommandManager::validate(const vector<string> &args) {
    if (args.size() < 3 || args[2] != QUERY_PARAMS_SEPERATOR) {
        throw ClientException(STATUS_400_BAD_REQUEST, "format of request is not valid");
    }
}

Command CommandManager::findCommand(HttpMethod method, const string &route, int argsCount) {
    if (method == HttpMethod::POST && route == SIGNUP_COMMAND) {
        return Command::SIGNUP;
    } else if (method == HttpMethod::POST && route == LOGOUT_COMMAND) {
        return Command::LOGOUT;
    } else if (method == HttpMethod::POST && route == LOGIN_COMMAND) {
        return Command::LOGIN;
    } else if (method == HttpMethod::GET && route == GET_USER_COMMAND && argsCount < 4) {
        return Command::GET_USERS;
    } else if (method == HttpMethod::GET && route == GET_USER_COMMAND) {
        return Command::GET_USER;
    } else if (method == HttpMethod::GET && route == GET_MUSICS_COMMAND && argsCount < 4) {
        return Command::GET_MUSICS;
    } else if (method == HttpMethod::GET && route == GET_MUSICS_COMMAND) {
        return Command::GET_MUSIC;
    } else if (method == HttpMethod::POST && route == ONE_MUSIC_COMMAND) {
        return Command::CREATE_MUSIC;
    } else if (method == HttpMethod::DELETE && route == ONE_MUSIC_COMMAND) {
        return Command::DELETE_MUSIC;
    } else if (method == HttpMethod::GET && route == GET_ARTIST_MUSICS_COMMAND) {
        return Command::GET_ARTIST_MUSICS;
    } else if (method == HttpMethod::GET && route == SEARCH_MUSIC_COMMAND) {
        return Command::SEARCH_MUSIC;
    } else if (method == HttpMethod::POST && route == PLAYLIST_ACTIONS_COMMAND) {
        return Command::ADD_PLAY_LIST;
    } else if (method == HttpMethod::GET && route == PLAYLIST_ACTIONS_COMMAND) {
        return Command::GET_PLAY_LIST;
    } else if (method == HttpMethod::PUT && route == ADD_MUSIC_TO_PLAYLIST_COMMAND) {
        return Command::ADD_MUSIC_TO_PLAY_LIST;
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

void CommandManager::handleLogout(Database* db) {
    UsersController controller = UsersController(db);
    return controller.logout();
}

void CommandManager::handleLogin(const vector<string> &args, Database* db) {
    UsersController controller = UsersController(db);
    string username = findArgValue(args, "username");
    string password = findArgValue(args, "password");

    if (username.empty() || password.empty()) {
        cout << "empty!!\n";
        throw ClientException(STATUS_400_BAD_REQUEST, "insufficient request params for signup");
    }

    cout << "passed arg conditions in login!!\n";
    return controller.login(username, password);
}

void CommandManager::mapCommandToController(Command c, const vector<string> &args, Database* db) {
    switch (c) {
    case Command::SIGNUP: {
        cout << "handling signup...\n";
        return handleSignUp(args, db);
    }
    case Command::LOGOUT: {
        cout << "handling logout...\n";
        return handleLogout(db);
    }
    case Command::LOGIN: {
        cout << "handling login...\n";
        return handleLogin(args, db);
    }
    case Command::GET_USERS: {
        cout << "handling get many users...\n";
        return handleGetManyUsers(args, db);
    }
    case Command::GET_USER: {
        cout << "handling get one user...\n";
        return handleGetSingleUser(args, db);
    }
    case Command::GET_MUSICS: {
        cout << "Handling getting musics...\n";
        return handleGetManyMusics(args, db);
    }
    case Command::GET_MUSIC: {
        cout << "handlign get music details...\n";
        return handleGetOneMusic(args, db);
    }
    case Command::GET_ARTIST_MUSICS: {
        cout << "getting regitered musics...\n";
        return handleGetArtistMusics(args, db);
    }
    case Command::CREATE_MUSIC: {
        cout << "creating and sharing music...\n";
        return handleAddMusic(args, db);
    }
    case Command::DELETE_MUSIC: {
        cout << "deleting music...\n";
        return handleDeleteMusic(args, db);   
    }
    case Command::ADD_PLAY_LIST: {
        cout << "adding playlist...\n";
        return handleAddPlayList(args, db);
    }
    case Command::GET_PLAY_LIST: {
        cout << "getting playlist for user\n";
        return handleGetManyPlayLists(args, db);
    }
    case Command::ADD_MUSIC_TO_PLAY_LIST: {
        cout << "adding music to playlist...\n";
        return handleAddSongToPlayList(args, db);
    }
    case Command::SEARCH_MUSIC: {
        cout << "searching music...\n";
        return handleSearchMusic(args, db);
    }
    default:
        cout << "GOING TO DEFAULT\n";
        break;
    }
}

void CommandManager::process(const vector<string> &args, Database* db) {
    HttpMethod method = getRequestMode(args[0]);
    Command command = findCommand(method, args[1], args.size());
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

void CommandManager::handleGetSingleUser(const vector<string> &args, Database* db) {
    UsersController controller = UsersController(db);
    string id = findArgValue(args, "id");
    
    if (!is_number(id)) {
        throw ClientException(400, "id should be a positive number");
    }

    return controller.getOneUser(stoi(id));
}


void CommandManager::handleGetManyUsers(const vector<string> &args, Database* db) {
    UsersController controller = UsersController(db);
    return controller.getAllUsers();
}

void CommandManager::handleGetManyMusics(const vector<string> &args, Database* db) {
    MusicsController controller(db);
    controller.getAllMusics();
}

void CommandManager::handleGetOneMusic(const vector<string> &args, Database* db) {
    string id = findArgValue(args, "id");
    MusicsController controller = MusicsController(db);
    return controller.getOneMusic(stoi(id));
}

void CommandManager::handleGetArtistMusics(const vector<string> &args, Database* db) {
    MusicsController controller(db);
    return controller.getCurrentArtistMusics();
}

void CommandManager::handleAddPlayList(const vector<string> &args, Database* db) {
    string name = findArgValue(args, "name");
    MusicsController controller(db);
    return controller.createPlaylist(name);
}

void CommandManager::handleAddSongToPlayList(const vector<string> &args, Database *db) {
    string songId = findArgValue(args, "id");
    string plName = findArgValue(args, "name");
    MusicsController controller(db);
    return controller.addMusicToPlaylist(stoi(songId), plName);
}

void CommandManager::handleSearchMusic(const vector<string> &args, Database* db) {

}

void CommandManager::handleGetManyPlayLists(const vector<string> &args, Database* db) {

}

void CommandManager::handleAddMusic(const vector<string> &args, Database* db) {
    string title = findArgValue(args, "title");
    string path = findArgValue(args, "path");
    string year = findArgValue(args, "year");
    string album = findArgValue(args, "album");
    string durationTime = findArgValue(args, "duration");
    string tags = findArgValue(args, "tags");

    vector<string> tagsList;
    string tag;
    istringstream ss(tags);
    while (getline(ss, tag, ';')) {
        tagsList.push_back(tag);
    }

    MusicsController controller = MusicsController(db);
    return controller.createMusic(title, path, album, stoi(year), durationTime, tagsList);
}

void CommandManager::handleDeleteMusic(const vector<string> &args, Database* db) {
    string id = findArgValue(args, "id");
    MusicsController controller(db);
    return controller.deleteMusic(stoi(id));
}
