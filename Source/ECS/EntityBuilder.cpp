#include "EntityBuilder.h"
#include "EntityManager.h"
#include "Components/Components.h"
#include "Graphics/Voxel/Primitive/Cube.h"
#include <glm/glm.hpp>

std::shared_ptr<Entity> EntityBuilder::geometry() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Octree,
        ComponentType::Render,
        ComponentType::Physics,
    };
    std::shared_ptr<Entity> entity = EntityManager::get()->createComponents(types);

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::cube() {
    return geometry();
}

std::shared_ptr<Entity> EntityBuilder::avatar() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Movement,
        ComponentType::Camera
    };
    return EntityManager::get()->createComponents(types);
}

std::shared_ptr<Entity> EntityBuilder::camera() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Movement, // TODO: take from to avatar
        ComponentType::Camera
    };
    std::shared_ptr<Entity> entity = EntityManager::get()->createComponents(types);

    auto movementComponent = static_cast<MovementComponent*>(entity->components[ComponentType::Movement].get());
    movementComponent->moveSpeed = 1.0;
    movementComponent->rotateSpeed = 0.05;

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::freeCamera() {
    std::vector<ComponentType> types = {
        ComponentType::Transform,
        ComponentType::Camera,
        ComponentType::Movement
    };

    std::shared_ptr<Entity> entity = EntityManager::get()->createComponents(types);

    auto movementComponent = static_cast<MovementComponent*>(entity->components[ComponentType::Movement].get());
    movementComponent->moveSpeed = 1.0;
    movementComponent->rotateSpeed = 0.05;
    movementComponent->free = true;

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::light() {
    std::vector<ComponentType> types = {
        ComponentType::Transform,
        ComponentType::Light,
    };
    return EntityManager::get()->createComponents(types);
}
