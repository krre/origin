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

class Entity : public Core::Object {

public:
    Entity(Entity* parent = nullptr);
    Entity(Core::EntityId id, Entity* parent = nullptr);
    ~Entity();

    Core::EntityId getId() const { return id; }
    static void setIdCounter(Core::EntityId id);

    void addComponent(const std::shared_ptr<Component>& component);
    Component* getComponent(Component::Type type);
    void removeComponent(Component::Type type);

    TransformComponent* getTransform();
    CameraComponent* getCamera();
    MovementComponent* getMovement();
    PhysicsComponent* getPhysics();
    OctreeComponent* getOctree();

private:
    Core::EntityId id;
    static Core::EntityId counter;
    std::map<Component::Type, std::shared_ptr<Component>> components;
};

} // Origin
