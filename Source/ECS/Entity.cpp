#include "Entity.h"
#include "Components/Components.h"

namespace Origin {

Core::EntityId Entity::counter = 0;

Entity::Entity(Entity* parent) : Object(parent) {
    id = counter++;
}

Entity::Entity(Core::EntityId id, Entity* parent) : Object(parent) {
    this->id = id;
}

Entity::~Entity() {

}

void Entity::setIdCounter(Core::EntityId id) {
    counter = id;
}

void Entity::addComponent(const std::shared_ptr<Component>& component) {
    components[component->getType()] = component;
}

Component* Entity::getComponent(Component::Type type) {
    return components[type].get();
}

void Entity::removeComponent(Component::Type type) {
    components.erase(type);
}

TransformComponent* Entity::getTransform() {
    return static_cast<TransformComponent*>(components[Component::Type::Transform].get());
}

CameraComponent* Entity::getCamera() {
    return static_cast<CameraComponent*>(components[Component::Type::Camera].get());
}

MovementComponent* Entity::getMovement() {
    return static_cast<MovementComponent*>(components[Component::Type::Movement].get());
}

PhysicsComponent* Entity::getPhysics() {
    return static_cast<PhysicsComponent*>(components[Component::Type::Physics].get());
}

OctreeComponent* Entity::getOctree() {
   return static_cast<OctreeComponent*>(components[Component::Type::Octree].get());
}

} // Origin
