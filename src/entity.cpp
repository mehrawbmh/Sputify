#include "../headers/entity.hpp"

bool Entity::isDeleted() const {
    return this->deleted;
}

void Entity::markAsDeleted() {
    this->deleted = true;
}
