#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>

using EntityId = uint64_t;

class Entity : Object {

public:
    Entity(EntityId id = 0);
    virtual ~Entity();

    template <typename T> std::shared_ptr<T> addComponent() {
        auto component = std::make_shared<T>();
        components[component->getType()] = component;
        return component;
    }

    void removeComponent(Component::Type type);
    Component *getComponent(Component::Type type);
    void clearComponents();

    EntityId getId() { return id; }
    std::map<Component::Type, std::shared_ptr<Component>> getComponents() { return components; }

private:
    std::map<Component::Type, std::shared_ptr<Component>> components;
    EntityId id;
};
