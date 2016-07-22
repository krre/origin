#pragma once
#include "../Core/Object.h"
#include "Component.h"
#include <map>

using EntityId = uint64_t;

class Entity : public Object {

public:
    Entity(EntityId id = 0);
    EntityId getId() { return id; }
    std::map<Component::Type, std::shared_ptr<Component>> components;
    bool enable = true;

private:
    EntityId id;
};
