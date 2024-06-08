#pragma once
#include "ecs/System.h"
#include "ecs/Entity.h"
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
    std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;
    std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> m_dispatcher;
    std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;
    std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
};
