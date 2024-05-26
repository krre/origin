#pragma once
#include "ECS/System.h"
#include "ECS/Entity.h"
#include <btBulletDynamicsCommon.h>

class PhysicsSystem : public System {

public:
    PhysicsSystem(EntityManager* entityManager);
    ~PhysicsSystem();
    void process(float dt) override;
    void addRigidBody(Entity* entity);
    void createRigidBody(Entity* entity);
    void createCollisionShape(Entity* entity);
    void createMotionState(Entity* entity);
private:
    std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> overlappingPairCache;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
};
