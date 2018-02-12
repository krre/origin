#include "EntityBuilder.h"
#include "EntityManager.h"
#include "Components/Components.h"
#include "Graphics/Voxel/Primitive/Cube.h"
#include <glm/glm.hpp>

namespace Origin {

EntityBuilder::EntityBuilder(EntityManager* entityManager) : entityManager(entityManager) {

}

std::shared_ptr<Entity> EntityBuilder::geometry() {
    std::vector<Component::Type> types = {
        Component::Type::Node,
        Component::Type::Transform,
        Component::Type::Octree,
        Component::Type::Render,
        Component::Type::Physics,
    };
    std::shared_ptr<Entity> entity = entityManager->createComponents(types);

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::cube() {
    return geometry();
}

std::shared_ptr<Entity> EntityBuilder::avatar() {
    std::vector<Component::Type> types = {
        Component::Type::Node,
        Component::Type::Transform,
        Component::Type::Movement,
        Component::Type::Camera
    };
    return entityManager->createComponents(types);
}

std::shared_ptr<Entity> EntityBuilder::camera() {
    std::vector<Component::Type> types = {
        Component::Type::Node,
        Component::Type::Transform,
        Component::Type::Movement, // TODO: take from to avatar
        Component::Type::Camera
    };
    std::shared_ptr<Entity> entity = entityManager->createComponents(types);

    auto movementComponent = static_cast<MovementComponent*>(entity->components[Component::Type::Movement].get());
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

    std::shared_ptr<Entity> entity = entityManager->createComponents(types);

    auto movementComponent = static_cast<MovementComponent*>(entity->components[Component::Type::Movement].get());
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
    return entityManager->createComponents(types);
}

} // Origin
