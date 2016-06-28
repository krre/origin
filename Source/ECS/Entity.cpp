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

Component* Entity::addComponent(ComponentType type) {
    switch (type) {
    case ComponentType::Transform:
        components[type] = new TransformComponent();
        break;
    case ComponentType::Render:
        components[type] = new RenderComponent();
        break;
    case ComponentType::Node:
        components[type] = new NodeComponent();
        break;
    case ComponentType::Camera:
        components[type] = new CameraComponent();
        break;
    case ComponentType::Input:
        components[type] = new InputComponent();
        break;
    default:
        return nullptr;
    }

    return components[type];
}

void Entity::removeComponent(ComponentType type) {
    delete components.at(type);
    components.erase(type);
}

const Component* Entity::getComponent(ComponentType type) {
    return components.at(type);
}

void Entity::clearComponents() {
    for (auto it: components) {
        delete it.second;
    }
    components.clear();
}
