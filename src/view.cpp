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
