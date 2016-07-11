#pragma once
#include "../Core/Object.h"
#include "Entity.h"
#include <list>

enum class SystemType {
    None,
    Input,
    Render,
    Transform,
    Node
};

class System : public Object {

public:
    System();
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void clearEntities();

    virtual void process(float dt) = 0;

    SystemType getType() { return type; }

protected:
    std::list<Entity*> entities;
    SystemType type = SystemType::None;
};
