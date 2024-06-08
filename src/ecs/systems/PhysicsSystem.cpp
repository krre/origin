#include "PhysicsSystem.h"
#include "ecs/components/Components.h"

PhysicsSystem::PhysicsSystem(EntityManager* entityManager) : System(entityManager) {
    m_type = System::Type::Physics;

    m_collisionConfiguration.reset(new btDefaultCollisionConfiguration);
    m_dispatcher.reset(new btCollisionDispatcher(m_collisionConfiguration.get()));
    m_overlappingPairCache.reset(new btDbvtBroadphase);
    m_solver.reset(new btSequentialImpulseConstraintSolver);

    m_dynamicsWorld.reset(new btDiscreteDynamicsWorld(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get()));
    m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

PhysicsSystem::~PhysicsSystem() {
    m_dynamicsWorld.release();
    m_solver.release();
    m_overlappingPairCache.release();
    m_dispatcher.release();
    m_collisionConfiguration.release();
}

void PhysicsSystem::process(float dt) {
//    dynamicsWorld->stepSimulation(dt, 10);
}

void PhysicsSystem::addRigidBody(Entity* entity) {
    PhysicsComponent* pc = entity->physics();
    m_dynamicsWorld->addRigidBody(pc->rigidBody.get());
}

void PhysicsSystem::createRigidBody(Entity* entity) {
    PhysicsComponent* pc = entity->physics();
    pc->rigidBody.reset(new btRigidBody(pc->mass, pc->motionState.get(), pc->collisionShape.get()));
}

void PhysicsSystem::createCollisionShape(Entity* entity) {
    PhysicsComponent* pc = entity->physics();
    TransformComponent* tc = entity->transform();
    btScalar scale = btScalar(tc->scale) / 2.0;
    pc->collisionShape.reset(new btBoxShape(btVector3(scale, scale, scale)));
}

void PhysicsSystem::createMotionState(Entity* entity) {
    PhysicsComponent* pc = entity->physics();
    TransformComponent* tc = entity->transform();
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(tc->position.x, tc->position.y, tc->position.z));
    pc->motionState.reset(new btDefaultMotionState(transform));
}
