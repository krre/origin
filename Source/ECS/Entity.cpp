#include "Entity.h"
#include "Components/Components.h"
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

Component* Entity::createComponent(Component::Type type) {
    switch (type) {
    case Component::Type::Camera:
        components[type] = std::make_shared<CameraComponent>();
        break;
    case Component::Type::Input:
        components[type] = std::make_shared<InputComponent>();
        break;
    case Component::Type::Material:
        components[type] = std::make_shared<MaterialComponent>();
        break;
    case Component::Type::Mesh:
        components[type] = std::make_shared<MeshComponent>();
        break;
    case Component::Type::Movement:
        components[type] = std::make_shared<MovementComponent>();
        break;
    case Component::Type::Node:
        components[type] = std::make_shared<NodeComponent>();
        break;
    case Component::Type::Render:
        components[type] = std::make_shared<RenderComponent>();
        break;
    case Component::Type::Transform:
        components[type] = std::make_shared<TransformComponent>();
        break;
    case Component::Type::MotionController:
        components[type] = std::make_shared<MotionControllerComponent>();
        break;
    }

    return components[type].get();
}

void Entity::createComponents(std::vector<Component::Type> types) {
    for (auto type : types) {
        createComponent(type);
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

void Entity::clearComponents() {
    components.clear();
}
