#include "Entity.h"

Entity::Entity() {

}

void Entity::addComponent(const Component& component) {
    components[component.getType()] = component;
}

void Entity::removeComponent(const Component::Type &type) {
    components.erase(type);
}

const Component &Entity::getComponent(const Component::Type &type) {
    return components.at(type);
}

void Entity::clear() {
    components.clear();
}
