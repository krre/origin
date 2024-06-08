#include "Entity.h"
#include "components/Components.h"

Core::EntityId Entity::s_counter = 0;

Entity::Entity(Entity* parent) : Object(parent) {
    m_id = s_counter++;
}

Entity::Entity(Core::EntityId id, Entity* parent) : Object(parent) {
    this->m_id = id;
}

Entity::~Entity() {

}

void Entity::setIdCounter(Core::EntityId id) {
    s_counter = id;
}

void Entity::addComponent(const std::shared_ptr<Component>& component) {
    m_components[component->type()] = component;
}

Component* Entity::component(Component::Type type) {
    return m_components[type].get();
}

void Entity::removeComponent(Component::Type type) {
    m_components.erase(type);
}

TransformComponent* Entity::transform() {
    return static_cast<TransformComponent*>(m_components[Component::Type::Transform].get());
}

CameraComponent* Entity::camera() {
    return static_cast<CameraComponent*>(m_components[Component::Type::Camera].get());
}

MovementComponent* Entity::movement() {
    return static_cast<MovementComponent*>(m_components[Component::Type::Movement].get());
}

PhysicsComponent* Entity::physics() {
    return static_cast<PhysicsComponent*>(m_components[Component::Type::Physics].get());
}

OctreeComponent* Entity::octree() {
   return static_cast<OctreeComponent*>(m_components[Component::Type::Octree].get());
}
