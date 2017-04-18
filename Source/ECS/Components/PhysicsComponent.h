#pragma once
#include "ECS/Component.h"
#include <btBulletDynamicsCommon.h>

class PhysicsComponent : public Component {

public:
    PhysicsComponent() { type = ComponentType::Physics; }
    std::unique_ptr<btRigidBody> rigidBody;
    std::unique_ptr<btCollisionShape> collisionShape;
    std::unique_ptr<btDefaultMotionState> motionState;
    btScalar mass = 0;
};
