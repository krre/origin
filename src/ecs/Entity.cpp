#include "Entity.h"
#include "components/Components.h"

Core::EntityId Entity::counter = 0;

Entity::Entity(Entity* parent) : Object(parent) {
    m_id = counter++;
}

Entity::Entity(Core::EntityId id, Entity* parent) : Object(parent) {
    this->m_id = id;
}

Entity::~Entity() {

}

void Entity::setIdCounter(Core::EntityId id) {
    counter = id;
}

void Entity::addComponent(const std::shared_ptr<Component>& component) {
    components[component->type()] = component;
}

Component* Entity::component(Component::Type type) {
    return components[type].get();
}

void Entity::removeComponent(Component::Type type) {
    components.erase(type);
}

TransformComponent* Entity::transform() {
    return static_cast<TransformComponent*>(components[Component::Type::Transform].get());
}

CameraComponent* Entity::camera() {
    return static_cast<CameraComponent*>(components[Component::Type::Camera].get());
}

MovementComponent* Entity::movement() {
    return static_cast<MovementComponent*>(components[Component::Type::Movement].get());
}

PhysicsComponent* Entity::physics() {
    return static_cast<PhysicsComponent*>(components[Component::Type::Physics].get());
}

OctreeComponent* Entity::octree() {
   return static_cast<OctreeComponent*>(components[Component::Type::Octree].get());
}
