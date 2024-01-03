#include "../headers/view.hpp"
#include <algorithm>

bool sortPlaylistsWithName(PlayList* p1, PlayList* p2) {
    return p1->getTitle() < p2->getTitle();
}

bool sortUsersByUsername(BaseUser* u1, BaseUser* u2) {
    return u1->getUsername() < u2->getUsername();
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

string View::showUserDetail(BaseUser *user, Database* db) {
    if (user == nullptr) {
        return RESOPNSE_404_NOT_FOUND + "\n";
    }

    string response;
    string mode = (user->canCreatePlayList()) ? "user" : "artist";

    response = response + "ID: " + to_string(user->getId()) + "\n";
    response = response + "Mode: " + mode + "\n";
    response = response + "Username: " + user->getUsername() + "\n";

    if (user->canCreatePlayList()) {
        response = response + "Playlists: ";
        response = response + this->getPlayListsFormatted(user->getId(), db);
    } else if (user->canShareMusic()) {
        response = response + "Songs: ";
        response = response + this->getSongsFormatted(user->getId(), db);
    }

    return response;
}

string View::getSongsFormatted(int artistId, Database* db) {
    string result;
    for (Music* music: db->getAllMusics()) {
        if (!music->isDeleted() && music->getArtist()->getId() == artistId) {
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
    if (users.size() == 0) {
        return RESOPNSE_201_NO_RESOPNSE;
    }
    sort(users.begin(), users.end(), sortUsersByUsername);

    string response = "ID, Mode, Username, Playlists_number/Songs_number\n";
    for (auto const &user: users) {
        response += to_string(user->getId()) + ", ";
        response += ((user->canCreatePlayList()) ? "user" : "artist");
        response += ", ";
        response += user->getUsername() + ", ";
        int count = this->getPlOrSongsCount(user, db);
        response = response + to_string(count);
        response += "\n";
    }

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

string View::showMusicDetail(Music* music) {
    if (music == nullptr) {
        return RESOPNSE_404_NOT_FOUND;
    }

    string response = "ID, Name, Artist, Year, Album, Tags, Duration\n";
    response += this->getMusicDetail(music);

    return response;
}

string View::showMusicsList(vector<Music*> musics) {
    if (musics.size() == 0) {
        return RESOPNSE_201_NO_RESOPNSE + "\n";
    }

    string response = "ID, Name, Artist\n";
    for (Music* music: musics) {
        response += to_string(music->getId()) + ", " + music->getName() + ", " + music->getArtist()->getUsername() + "\n";
    }

    return response;
}

string View::showMusicListDetailed(vector<Music*> musics) {
    if (musics.size() == 0) {
        return RESOPNSE_201_NO_RESOPNSE + "\n";
    }

    string response = "ID, Name, Artist, Year, Album, Tags, Duration\n";
    for (Music* music: musics) {
        response += this->getMusicDetail(music) + "\n";
    }

    return response;
}

string View::showPlaylists(vector<PlayList*> playlists) {
    if (playlists.size() == 0) {
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
