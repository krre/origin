#include "Entity.h"

namespace Origin {

EntityId Entity::counter = 0;

Entity::Entity(Entity* parent) : Object(parent) {
    id = counter++;
}

Entity::Entity(EntityId id, Entity* parent) : Object(parent) {
    this->id = id;
}

void Entity::setIdCounter(EntityId id) {
    counter = id;
}

} // Origin
