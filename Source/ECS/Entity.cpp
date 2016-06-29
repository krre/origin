#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/RenderComponent.h"
#include "Components/NodeComponent.h"
#include "Components/CameraComponent.h"
#include "Components/InputComponent.h"
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



void Entity::removeComponent(ComponentType type) {
    delete components.at(type);
    components.erase(type);
}

const Component* Entity::getComponent(ComponentType type) {
    Component* component = nullptr;
    try {
        component = components.at(type);
    } catch (...) {

    }

    return component;
}

void Entity::clearComponents() {
    for (auto it: components) {
        delete it.second;
    }
    components.clear();
}
