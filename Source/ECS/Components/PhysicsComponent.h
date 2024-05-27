#pragma once
#include "ECS/Component.h"
#include <btBulletDynamicsCommon.h>
#include <memory>

class PhysicsComponent : public Component {

public:
    PhysicsComponent() = default;
    Type getType() const override { return Component::Type::Physics; }

    std::unique_ptr<btRigidBody> rigidBody;
    std::unique_ptr<btCollisionShape> collisionShape;
    std::unique_ptr<btDefaultMotionState> motionState;
    btScalar mass = 0;
};
