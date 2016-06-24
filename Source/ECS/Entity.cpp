#include "Entity.h"
#include <chrono>

Entity::Entity(EntityId id) {
    if (id) {
        this->id = id;
    } else {
        // Get id as nanoseconds count from Epoch
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        this->id = duration_cast<nanoseconds>(now.time_since_epoch()).count();
    }
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
