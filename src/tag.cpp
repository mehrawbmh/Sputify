#include "../headers/tag.hpp"

Tag::Tag(string name): title(name) {}

string Tag::getTitle() {
    return this->title;
}
