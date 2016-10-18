#pragma once
#include "../System.h"
#include "../Entity.h"
#include <btBulletDynamicsCommon.h>

class PhisicsSystem : public System {

public:
    PhisicsSystem();
    void process(float dt) override;
    void addRigidBody(Entity* entity);
    void createCollisionShape(Entity* entity);
private:
    std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> overlappingPairCache;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
};
