#include "../headers/play_list.hpp"

PlayList::PlayList(string title_, int user): title(title_), userId(user) {}

string PlayList::getTitle() {
    return this->title;
}

int PlayList::getUserId() {
    return this->userId;
}
