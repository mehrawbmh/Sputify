#include "../headers/entity.hpp"

bool Entity::isDeleted() {
    return this->deleted;
}

void Entity::markAsDeleted() {
    this->deleted = true;
}
