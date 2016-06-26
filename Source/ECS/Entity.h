#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>

typedef uint64_t EntityId;

class Entity : Object {

public:
    Entity(EntityId id = 0);

    void addComponent(const Component& component);
    void removeComponent(const ComponentType& type);
    const Component& getComponent(const ComponentType& type);
    void clear();

    EntityId getId() { return id; }

private:
    map<ComponentType, Component> components;
    EntityId id;
};
