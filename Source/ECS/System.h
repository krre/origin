#pragma once
#include "../Core/Object.h"
#include "Entity.h"
#include <list>

class System : public Object {

public:
    System();
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void clearEntities();
    virtual void update(float dt) = 0;

protected:
    list<Entity*> entities;
};
