#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>
#include <vector>

using EntityId = uint64_t;

class Entity : public Object {

public:
    Entity(EntityId id = 0);
    EntityId getId() { return id; }
    std::map<Component::Type, std::shared_ptr<Component>> components;

    Component* createComponent(Component::Type type);
    void createComponents(std::vector<Component::Type> types);
    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(Component::Type type);
    Component* getComponent(Component::Type type);

private:
    EntityId id;
};
