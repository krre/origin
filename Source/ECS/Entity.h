#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>

using EntityId = uint64_t;

class Entity : Object {

public:
    Entity(EntityId id = 0);
    virtual ~Entity();

    template <typename T> T* addComponent() {
        T* component = new T;
        components[component->getType()] = component;
        return component;
    }

    void removeComponent(ComponentType type);
    Component *getComponent(ComponentType type);
    void clearComponents();

    EntityId getId() { return id; }
    std::map<ComponentType, Component*> getComponents() { return components; }

private:
    std::map<ComponentType, Component*> components;
    EntityId id;
};
