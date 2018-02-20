#pragma once
#include "Core/Object.h"
#include "Component.h"
#include <map>

namespace Origin {

class Entity : public Object {

public:
    Entity(Entity* parent = nullptr);
    Entity(EntityId id, Entity* parent = nullptr);
    ~Entity();

    EntityId getId() { return id; }
    static void setIdCounter(EntityId id);

    void addComponent(const std::shared_ptr<Component>& component);

    std::map<Component::Type, std::shared_ptr<Component>> components;

private:
    EntityId id;
    static EntityId counter;
};

} // Origin
