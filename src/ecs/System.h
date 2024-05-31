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

    Type type() const { return m_type; }

    void setActive(bool active);
    bool active() const { return m_active; }

protected:
    Type m_type = Type::None;
    bool m_active = true;
    EntityManager* entityManager;
};
