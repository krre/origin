#pragma once
#include "../Component.h"
#include <btBulletDynamicsCommon.h>

class PhisicsComponent : public Component {

public:
    PhisicsComponent() { type = ComponentType::Phisics; }
    std::unique_ptr<btRigidBody> rigidBody;
    std::unique_ptr<btCollisionShape> collisionShape;
};
