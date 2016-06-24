#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>

typedef unsigned int EntityId;

class Entity : Object {

public:
    Entity();

    void addComponent(const Component& component);
    void removeComponent(const Component::Type& type);
    const Component& getComponent(const Component::Type& type);
    void clear();

    EntityId getId() { return id; }

private:
    map<Component::Type, Component> components;
    EntityId id;
};
