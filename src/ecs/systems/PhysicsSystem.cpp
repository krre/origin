#include "PhysicsSystem.h"
#include "ecs/components/Components.h"

PhysicsSystem::PhysicsSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Physics;

    collisionConfiguration.reset(new btDefaultCollisionConfiguration);
    dispatcher.reset(new btCollisionDispatcher(collisionConfiguration.get()));
    overlappingPairCache.reset(new btDbvtBroadphase);
    solver.reset(new btSequentialImpulseConstraintSolver);

    dynamicsWorld.reset(new btDiscreteDynamicsWorld(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get()));
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

PhysicsSystem::~PhysicsSystem() {
    dynamicsWorld.release();
    solver.release();
    overlappingPairCache.release();
    dispatcher.release();
    collisionConfiguration.release();
}

void PhysicsSystem::process(float dt) {
//    dynamicsWorld->stepSimulation(dt, 10);
}

void PhysicsSystem::addRigidBody(Entity* entity) {
    PhysicsComponent* pc = entity->getPhysics();
    dynamicsWorld->addRigidBody(pc->rigidBody.get());
}

void PhysicsSystem::createRigidBody(Entity* entity) {
    PhysicsComponent* pc = entity->getPhysics();
    pc->rigidBody.reset(new btRigidBody(pc->mass, pc->motionState.get(), pc->collisionShape.get()));
}

void PhysicsSystem::createCollisionShape(Entity* entity) {
    PhysicsComponent* pc = entity->getPhysics();
    TransformComponent* tc = entity->getTransform();
    btScalar scale = btScalar(tc->scale) / 2.0;
    pc->collisionShape.reset(new btBoxShape(btVector3(scale, scale, scale)));
}

void PhysicsSystem::createMotionState(Entity* entity) {
    PhysicsComponent* pc = entity->getPhysics();
    TransformComponent* tc = entity->getTransform();
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(tc->position.x, tc->position.y, tc->position.z));
    pc->motionState.reset(new btDefaultMotionState(transform));
}
