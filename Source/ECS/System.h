#pragma once
#include "Core/Object.h"
#include "ECSTypes.h"
#include <vector>

class EntityManager;

class System : public Object {

public:
    System();

    virtual void process(float dt) = 0;

    SystemType getType() const { return type; }

    void setActive(bool active);
    bool getActive() const { return active; }

protected:
    SystemType type = SystemType::None;
    bool active = true;
    static EntityManager* entityManager;
};
