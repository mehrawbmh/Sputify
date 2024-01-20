#include <algorithm>

#include "../headers/view.hpp"

bool sortPlaylistsWithName(PlayList* p1, PlayList* p2) {
    return p1->getTitle() < p2->getTitle();
}

bool sortUsersByUsername(BaseUser* u1, BaseUser* u2) {
    return u1->getUsername() < u2->getUsername();
}

string getMusicHtmlPage(string source, string detail) {
    string res = "<html lang='en'>"
        "<head>"
        "    <meta charset='UTF-8'>"
        "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
        "    <title>Music Page</title>"
        "</head>"
        "<body>"
        "<center>"
        "    <script>"
        "        var audio = new Audio('";
        string second = "');"
        "   function playAudio() {"
        "            audio.play();"
        "        }"
        "        function pauseAudio() {"
        "            audio.pause();"
        "        }"
        "    </script>"
        " <a href=\"/\"> <img src=\"/home.png\" alt=\"Home Logo\" style=\"width:5%;\"><br> </a>"
        "    <h1>Music detail</h1>"
        "    <button onclick='playAudio()'>Play</button>"
        "    <button onclick='pauseAudio()'>Pause</button> <br><br>";
        string third = detail + "</center>"
             "</body>"
              "</html>";
        
        return res + source + second + third;
}

string View::showResponse(int statusCode) {
    switch (statusCode) {
    case STATUS_200_SUCCESS:
        return RESOPNSE_200_SUCCESS;
    case STATUS_201_NO_RESOPNSE:
        return RESOPNSE_201_NO_RESOPNSE;
    case STATUS_400_BAD_REQUEST:
        return RESOPNSE_400_BAD_REQUEST;
    case STATUS_403_FORBIDDEN:
        return RESPONSE_403_FORBIDDEN;
    case STATUS_404_NOT_FOUND:
        return RESOPNSE_404_NOT_FOUND;
    default:
        throw logic_error("bad status code provided");
    }
}

string View::showSuccessResponse() {
    return showResponse(STATUS_200_SUCCESS);
}

string View::showUserDetail(BaseUser *user, Database* db) {
    if (user == nullptr) {
        return RESOPNSE_404_NOT_FOUND + "\n";
    }

    string response;
    response += "<!DOCTYPE html>";
    response += "<html>";
    response += "<body style=\"text-align: center;\">";
    response += " <a href=\"/\"> <img src=\"/home.png\" alt=\"Home Logo\" style=\"width:5%;\"><br> </a>";
    response += "<h1> Sputify </h1>";
    response += "<p style=\"font-family: 'Arial', sans-serif; font-size: 16px; color: #333; line-height: 1.5; text-align: center;\">";

    string mode = (user->canCreatePlayList()) ? "user" : "artist";

    response = response + "ID: " + to_string(user->getId()) + "<br>";
    response = response + "Mode: " + mode + "<br>";
    response = response + "Username: " + user->getUsername() + "<br>";

    response += "Followings: " + this->printUsernames(db->findManyUsersByIds(user->getFollowings())) + "<br>";
    response += "Followers: " + this->printUsernames(db->findManyUsersByIds(user->getFollowers())) + "<br>";
    
    if (user->canCreatePlayList()) {
        response = response + "Playlists: ";
        response = response + this->getPlayListsFormatted(user->getId(), db);
    } else if (user->canShareMusic()) {
        response = response + "Songs: ";
        response = response + this->getSongsFormatted(user->getId(), db);
    }
    response += "</p>";

    auto followings = db->getCurrentUser()->getFollowings();
    if (user->getId() != db->getCurrentUser()->getId() &&
        std::find(followings.begin(), followings.end(), user->getId()) == followings.end() ) {
        response += "<form method=\"post\" action=\"/follow?id=" + to_string(user->getId()) +" \" class=\"inline\"> <button type=\"submit\" name=\"submitButton\" value=\"submit\" class=\"link-button\"> Follow </button> </form> ";
    } else if(user->getId() != db->getCurrentUser()->getId()) {
        response += "<form method=\"post\" action=\"/unfollow?id=" + to_string(user->getId()) +" \" class=\"inline\"> <button type=\"submit\" name=\"submitButton2\" value=\"submit\" class=\"link-button\"> Unfollow </button> </form> ";
    }

    response += "</body>";
    response += "</html>";

    return response;
}

string View::printUsernames(vector<BaseUser*> users) {
    string result;
    if (users.empty()) {
        return "";
    }

    for (auto user: users) {
        result += user->getUsername() + ", ";
    }

    result.pop_back();
    result.pop_back();
    return result;
}

string View::getSongsFormatted(int artistId, Database* db) {
    string result;
    for (Music* music: db->getAllMusics(true)) {
        if (music->getArtist()->getId() == artistId) {
            result += music->getName() + ", ";
        }
    }

    if (result.empty()) {
        return "\n";
    }

    result.pop_back();
    result.pop_back();
    result += "\n";

    return result;
}

string View::getPlayListsFormatted(int userId, Database* db) {
    string result;
    for (PlayList* pl: db->getUserPlayList(userId)) {
        result += pl->getTitle() + ", ";
    }

    if (result.empty()) {
        return "\n";
    }

    result.pop_back();
    result.pop_back();
    result += "\n";

    return result;
}

int View::getPlOrSongsCount(BaseUser* user, Database* db) {
    if (user->canCreatePlayList()) {
        return db->getUserPlaylistCount(user);
    } else {
        return db->getArtistSongsCount(user);
    }
}

string View::showUsersList(vector<BaseUser*> users, Database* db) {
    if (users.empty()) {
        return RESOPNSE_201_NO_RESOPNSE;
    }
    sort(users.begin(), users.end(), sortUsersByUsername);

    string response;
    response += "<!DOCTYPE html>";
    response += "<html>";
    response += "<body style=\"text-align: center;\">";
    response += "<center>";
    response += " <a href=\"/\"> <img src=\"/home.png\" alt=\"Home Logo\" style=\"width:5%;\"><br> </a>";
    response += "<h1> Sputify </h1>";
    response += " <h2 style=\"color: red;\"> ID, Mode, Username, Playlists_number/Songs_number </h3> <br>";

    for (auto const &user: users) {
        response += "<p style=\"font-family: 'Arial', sans-serif; font-size: 24px; color: blue; line-height: 1.5; text-align: center;\">";
        response += to_string(user->getId()) + ", ";
        response += ((user->canCreatePlayList()) ? "user" : "artist");
        response += ", ";
        response += "<a href=\"/user?id=" + to_string(user->getId()) + "\" style=\"color: red;\">" + user->getUsername() + ", </a>";
        int count = this->getPlOrSongsCount(user, db);
        response += to_string(count);
        response += "\n";
        response += "</p>";
    }
    response += "</center>";
    response += "</body>";
    response += "</html>";
    return response;
}

string View::getMusicDetail(Music* music) {
    string response;
    
    response += to_string(music->getId()) + ", ";
    response += music->getName() + ", ";
    response += music->getArtist()->getUsername() + ", ";
    response += to_string(music->getYear()) + ", ";
    response += music->getAlbum() + ", ";

    for (Tag* tag: music->getTags()) {
        response += tag->getTitle() + ";";
    }

    response.pop_back();
    response += ", ";
    response += music->getDuration();

    return response;
}

string View::showMusicDetail(Music* music, Database* db) {
    if (music == nullptr) {
        return RESOPNSE_404_NOT_FOUND;
    }

    string detail = "ID, Name, Artist, Year, Album, Tags, Duration <br><br>";
    detail += "<p> " + this->getMusicDetail(music) + "</p>";
    
    auto user = db->getCurrentUser();
    if (user && user->canCreatePlayList()) {
        for (PlayList* pl: db->getUserPlayList(user->getId())) {
            if (std::find(pl->getSongs().begin(), pl->getSongs().end(), music) == pl->getSongs().end()) {
                detail += "<form method='post' action='/add-to-playlist?musicId=" + to_string(music->getId()) + "&playlistName=" + pl->getTitle() +
                        "'> <input type='submit' value='add to " + pl->getTitle() + " playlist '"
                        "style='display: block; width: 50%; padding: 10px;'> </form> <br> <br>";
            }
        }
    }
    
    return getMusicHtmlPage(music->getPath(), detail); 
}

string View::showMusicsList(const vector<Music*>& musics) {
    if (musics.empty()) {
        return RESOPNSE_201_NO_RESOPNSE + "\n";
    }

    string response = "ID, Name, Artist\n";
    for (Music* music: musics) {
        response += to_string(music->getId()) + ", " + music->getName() + ", " + music->getArtist()->getUsername() + "\n";
    }

    return response;
}

string View::showMusicListDetailed(const vector<Music*>& musics) {
    if (musics.empty()) {
        return RESOPNSE_201_NO_RESOPNSE + "\n";
    }

    string response;
    response += "<!DOCTYPE html>";
    response += "<html>";
    response += "<body style=\"text-align: center;\">";
    response += "<center>";
    response += " <a href=\"/\"> <img src=\"/home.png\" alt=\"Home Logo\" style=\"width:5%;\"><br> </a>";
    response += "<h1> Sputify </h1>";
    response += " <h2 style=\"color: darkblue;\"> ID, Name, Artist, Year, Album, Tags, Duration </h3> <br>";

    for (Music* music: musics) {
        response += "<h3 style='color: brown;'>" + this->getMusicDetail(music) + "</p> <a href='/music?id=" + to_string(music->getId()) + "'> (See detail)</a> <br>";
    }

    response += "</center>";
    response += "</body>";
    response += "</html>";

    return response;
}

string View::showPlaylists(vector<PlayList*> playlists) {
    if (playlists.empty()) {
        return RESOPNSE_201_NO_RESOPNSE + "\n";
    }

    sort(playlists.begin(), playlists.end(), sortPlaylistsWithName);
    string response = "Playlist_ID, Playlist_name, Songs_number, Duration\n";

    for (PlayList* playlist: playlists) {
        response += to_string(playlist->getId()) + ", ";
        response += playlist->getTitle() + ", ";
        response += to_string(playlist->getSongsCount()) + ", ";
        response += playlist->getPlaylistDuration();
        response += "\n";
    }

    return response;
}

string View::showPlaylistDetail(PlayList* playlist, Database* db) {
    return showMusicsList(playlist->getSongs());
}

string View::showRecommendedMusics(vector<Music*> songs) {
    if (songs.empty()) {
        return RESOPNSE_201_NO_RESOPNSE + "\n";
    }

    string response = "ID, Name, Artist, Likes\n";
    for (Music* music: songs) {
        response += to_string(music->getId()) + ", " +
            music->getName() + ", " +
            music->getArtist()->getUsername() + ", " +
            to_string(music->getLikesCount()) + "\n";
    }

    return response;
}

Response* View::redirectResponse(const string &url) {
    return Response::redirect(url);
}

