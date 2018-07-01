#pragma once
#include "Core/Object.h"
#include "Component.h"
#include <map>

namespace Origin {

class TransformComponent;
class CameraComponent;
class MovementComponent;
class PhysicsComponent;
class OctreeComponent;

class Entity : public Object {

public:
    Entity(Entity* parent = nullptr);
    Entity(EntityId id, Entity* parent = nullptr);
    ~Entity();

    EntityId getId() { return id; }
    static void setIdCounter(EntityId id);

    void addComponent(const std::shared_ptr<Component>& component);
    Component* getComponent(Component::Type type);
    void removeComponent(Component::Type type);

    TransformComponent* getTransform();
    CameraComponent* getCamera();
    MovementComponent* getMovement();
    PhysicsComponent* getPhysics();
    OctreeComponent* getOctree();

private:
    EntityId id;
    static EntityId counter;
    std::map<Component::Type, std::shared_ptr<Component>> components;
};

} // Origin
