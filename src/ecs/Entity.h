#pragma once
#include "Component.h"
#include <core/Object.h>
#include <map>

class TransformComponent;
class CameraComponent;
class MovementComponent;
class PhysicsComponent;
class OctreeComponent;

class Entity : public Core::Object {
public:
    Entity(Entity* parent = nullptr);
    Entity(Core::EntityId id, Entity* parent = nullptr);

    ~Entity();

    Core::EntityId id() const { return m_id; }
    static void setIdCounter(Core::EntityId id);

    void addComponent(const std::shared_ptr<Component>& component);
    Component* component(Component::Type type);
    void removeComponent(Component::Type type);

    TransformComponent* transform();
    CameraComponent* camera();
    MovementComponent* movement();
    PhysicsComponent* physics();
    OctreeComponent* octree();

private:
    Core::EntityId m_id;
    static Core::EntityId s_counter;
    std::map<Component::Type, std::shared_ptr<Component>> m_components;
};
