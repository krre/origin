#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>
#include <vector>

using EntityId = uint64_t;

class Entity : public Object {

public:
    Entity(EntityId id = 0);

    Component* createComponent(Component::Type type);
    void createComponents(std::vector<Component::Type> types);
    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(Component::Type type);
    Component* getComponent(Component::Type type);
    void clearComponents();

    EntityId getId() { return id; }
    std::map<Component::Type, std::shared_ptr<Component>> getComponents() { return components; }

private:
    std::map<Component::Type, std::shared_ptr<Component>> components;
    EntityId id;
};
