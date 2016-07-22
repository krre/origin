#include "EntityBuilder.h"
#include "Engine.h"
#include "Components/Components.h"
#include "../Graphics/Mesh/Plane.h"
#include "../Graphics/Mesh/Cube.h"
#include "../Graphics/Material.h"

std::shared_ptr<Entity> EntityBuilder::geometry() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Mesh,
        ComponentType::Material,
        ComponentType::Render,
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    MaterialComponent* materialComp = static_cast<MaterialComponent*>(entity->components[ComponentType::Material].get());
    materialComp->material = std::make_shared<Material>();
    materialComp->material->setColor(Color(0.2, 0.7f, 0.8f, 1));

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::plane() {
    std::shared_ptr<Entity> entity = geometry();

    MeshComponent* meshComp = static_cast<MeshComponent*>(entity->components[ComponentType::Mesh].get());
    meshComp->mesh = std::make_shared<Plane>();

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::cube() {
    std::shared_ptr<Entity> entity = geometry();

    MeshComponent* meshComp = static_cast<MeshComponent*>(entity->components[ComponentType::Mesh].get());
    meshComp->mesh = std::make_shared<Cube>();

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::avatar() {
    std::vector<ComponentType> types = {
        ComponentType::Node,
        ComponentType::Transform,
        ComponentType::Input,
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
    movementComponent->rotateSpeed = 0.1;

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
