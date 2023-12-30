#include "../headers/tag.hpp"

Tag::Tag(string name): title(name) {}

const string Tag::getTitle() const
{
    return this->title;
}
