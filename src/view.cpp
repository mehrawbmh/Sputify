#include "../headers/view.hpp"

string View::showResponse(int statusCode)
{
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

string View::showUserDetail(BaseUser *user)
{
    if (user == nullptr) {
        return RESOPNSE_404_NOT_FOUND;
    }

    string response;
    string mode = (user->canCreatePlayList()) ? "user" : "artist";

    response = response + "ID: " + to_string(user->getId()) + "\n";
    response = response + "Mode: " + mode + "\n";
    response = response + "Username: " + user->getUsername() + "\n";

    if (user->canCreatePlayList()) {
        response = response + "Playlists: ";
        // response = response + this->getPlayListsFormatted();
        //todo complete it
    } else if (user->canShareMusic()) {
        response = response + "Songs: ";
        // response = response + this->getSongsFormatted();
    }

    return response;
}

string View::showUsersList(vector<BaseUser*> users) {
    if (users.size() == 0) {
        return RESOPNSE_201_NO_RESOPNSE;
    }

    string response = "ID, Mode, Username, Playlists_number/Songs_number\n";
    for (auto const &user: users) {
        response += to_string(user->getId()) + ", ";
        response += ((user->canCreatePlayList()) ? "user" : "artist");
        response += ", ";
        response += user->getUsername() + ", ";
        // int count = (user->canCreatePlayList()) ? user.getSongs().size() : user.getPlaylists().size();
        // response = response + count;
        response += "\n";
    }

    return response;
}

string View::showMusicDetail(Music* music) {
    if (music == nullptr) {
        return RESOPNSE_404_NOT_FOUND;
    }
    string response = "ID, Name, Artist, Year, Album, Tags, Duration\n";
    response += to_string(music->getId()) + ", ";
    response += music->getName() + ", ";
    response += music->getArtist()->getUsername() + ", ";
    response += to_string(music->getYear()) + ", ";
    response += music->getAlbum() + ", ";

    cout << "here in view...\n";
    for (Tag* tag: music->getTags()) {
        cout << "again here\n";
        response += tag->getTitle() + ";";
    }
    cout << "here after view...\n";
    response.pop_back();
    response += ", ";
    response += music->getDuration();

    return response;
}

string View::showMusicsList(vector<Music*> musics) {
    if (musics.size() == 0) {
        return RESOPNSE_201_NO_RESOPNSE;
    }

    string response = "ID, Name, Artist\n";
    for (Music* music: musics) {
        response += to_string(music->getId()) + ", " + music->getName() + ", " + music->getArtist()->getUsername() + "\n";
    }

    return response;
}
