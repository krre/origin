#include "EntityBuilder.h"
#include "EntityManager.h"
#include "components/Components.h"
#include <glm/glm.hpp>

EntityBuilder::EntityBuilder(EntityManager* entityManager) : m_entityManager(entityManager) {

}

std::shared_ptr<Entity> EntityBuilder::geometry() {
    std::vector<Component::Type> types = {
        Component::Type::Transform,
        Component::Type::Octree,
        Component::Type::Render,
        Component::Type::Physics,
    };
    std::shared_ptr<Entity> entity = m_entityManager->createComponents(types);

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::cube() {
    return geometry();
}

std::shared_ptr<Entity> EntityBuilder::avatar() {
    std::vector<Component::Type> types = {
        Component::Type::Transform,
        Component::Type::Movement,
        Component::Type::Camera
    };
    return m_entityManager->createComponents(types);
}

std::shared_ptr<Entity> EntityBuilder::camera() {
    std::vector<Component::Type> types = {
        Component::Type::Transform,
        Component::Type::Movement, // TODO: take from to avatar
        Component::Type::Camera
    };
    std::shared_ptr<Entity> entity = m_entityManager->createComponents(types);

    MovementComponent* movementComponent = entity->movement();
    movementComponent->moveSpeed = 1.0;
    movementComponent->rotateSpeed = 0.05;

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::freeCamera() {
    std::vector<Component::Type> types = {
        Component::Type::Transform,
        Component::Type::Camera,
        Component::Type::Movement
    };

    std::shared_ptr<Entity> entity = m_entityManager->createComponents(types);

    MovementComponent* movementComponent = entity->movement();
    movementComponent->moveSpeed = 1.0;
    movementComponent->rotateSpeed = 0.05;
    movementComponent->free = true;

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::light() {
    std::vector<Component::Type> types = {
        Component::Type::Transform,
        Component::Type::Light,
    };
    return m_entityManager->createComponents(types);
}
