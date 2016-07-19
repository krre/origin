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

Entity::~Entity() {
    clearComponents();
}

void Entity::removeComponent(Component::Type type) {
    components.erase(type);
}

Component* Entity::getComponent(Component::Type type) {
    Component* component = nullptr;
    try {
        component = components.at(type).get();
    } catch (...) {

    }

    return component;
}

void Entity::clearComponents() {
    components.clear();
}
