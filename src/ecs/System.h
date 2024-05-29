#pragma once
#include <core/Object.h>

class EntityManager;

class System : public Core::Object {

public:

    enum class Type {
        Camera,
        Input,
        MovementController,
        Node,
        None,
        Octree,
        Physics,
        Render,
        Transform
    };

    System(EntityManager* entityManager);

    virtual void process(float dt) = 0;

    Type getType() const { return type; }

    void setActive(bool active);
    bool getActive() const { return active; }

protected:
    Type type = Type::None;
    bool active = true;
    EntityManager* entityManager;
};