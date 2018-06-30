#include "Entity.h"
#include "Components/Components.h"

namespace Origin {

EntityId Entity::counter = 0;

Entity::Entity(Entity* parent) : Object(parent) {
    id = counter++;
}

Entity::Entity(EntityId id, Entity* parent) : Object(parent) {
    this->id = id;
}

Entity::~Entity() {

}

void Entity::setIdCounter(EntityId id) {
    counter = id;
}

void Entity::addComponent(const std::shared_ptr<Component>& component) {
    components[component->getType()] = component;
}

TransformComponent* Entity::getTransform() {
    return static_cast<TransformComponent*>(components[Component::Type::Transform].get());
}

CameraComponent* Entity::getCamera() {
    return static_cast<CameraComponent*>(components[Component::Type::Camera].get());
}

MovementComponent* Entity::getMovement() {
    return static_cast<MovementComponent*>(components[Component::Type::Camera].get());
}

} // Origin
