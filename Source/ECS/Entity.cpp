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

void Entity::addComponent(std::shared_ptr<Component> component) {
    components[component->getType()] = component;
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

