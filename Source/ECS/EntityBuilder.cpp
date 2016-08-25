#include "EntityBuilder.h"
#include "Engine.h"
#include "Components/Components.h"
#include "../Graphics/Voxel/Primitive/Cube.h"
#include <glm/glm.hpp>

std::shared_ptr<Entity> EntityBuilder::geometry() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Octree,
        ComponentType::Material,
        ComponentType::Render,
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    MaterialComponent* materialComp = static_cast<MaterialComponent*>(entity->components[ComponentType::Material].get());
    materialComp->color = glm::vec3(1.0, 1.0f, 1.0f);

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::cube() {
    std::shared_ptr<Entity> entity = geometry();

    OctreeComponent* octreeComp = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
    octreeComp->octree = std::make_shared<Cube>();

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::avatar() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Movement,
        ComponentType::Camera
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::camera() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Movement, // TODO: take from to avatar
        ComponentType::Camera
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

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
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::light() {
    std::vector<ComponentType> types = {
        ComponentType::Transform,
        ComponentType::Light,
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    return entity;
}
