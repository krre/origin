#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>

class Entity : Object {

public:
    Entity();

    void addComponent(const Component& component);
    void removeComponent(const Component::Type& type);
    const Component& getComponent(const Component::Type& type);
    void clear();

    unsigned int getId() { return id; }

private:
    map<Component::Type, Component> components;
    unsigned int id;
};
