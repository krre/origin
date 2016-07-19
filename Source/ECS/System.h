#pragma once
#include "../Core/Object.h"
#include "Entity.h"
#include <vector>

class Engine;

class System : public Object {

public:
    enum class Type {
        None,
        Input,
        Render,
        Transform,
        Node
    };

    System();
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void clearEntities();

    virtual void process(float dt) = 0;

    Type getType() { return type; }

protected:
    std::vector<Entity*> entities;
    Type type = Type::None;
    static Engine* engine;
};
