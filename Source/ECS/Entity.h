#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>

typedef uint64_t EntityId;

class Entity : Object {

public:
    Entity(EntityId id = 0);
    virtual ~Entity();

    void addComponent(const ComponentType& type);
    void removeComponent(const ComponentType& type);
    const Component* getComponent(const ComponentType& type);
    void clearComponents();

    EntityId getId() { return id; }

private:
    map<ComponentType, Component*> components;
    EntityId id;
};
