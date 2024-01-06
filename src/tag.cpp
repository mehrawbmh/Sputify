#include <utility>

#include "../headers/tag.hpp"

Tag::Tag(string name): title(std::move(name)) {}

string Tag::getTitle() {
    return this->title;
}
