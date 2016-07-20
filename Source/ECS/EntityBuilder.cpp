#include "EntityBuilder.h"
#include "Engine.h"
#include "Components/Components.h"
#include "../Graphics/Model.h"
#include "../Graphics/Mesh/Plane.h"
#include "../Graphics/Material.h"

std::shared_ptr<Entity> EntityBuilder::ground() {
    std::vector<Component::Type> types = {
        Component::Type::Node,
        Component::Type::Transform,
        Component::Type::Mesh,
        Component::Type::Material,
        Component::Type::Render,
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    MeshComponent* meshComp = static_cast<MeshComponent*>(entity->components[Component::Type::Mesh].get());
    meshComp->mesh = std::make_shared<Plane>(1, 1);

    MaterialComponent* materialComp = static_cast<MaterialComponent*>(entity->components[Component::Type::Material].get());
    materialComp->material = std::make_shared<Material>();
    materialComp->material->setColor(Color(0.2, 0.7f, 0.8f, 1));

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::avatar() {
    std::vector<Component::Type> types = {
        Component::Type::Node,
        Component::Type::Transform,
        Component::Type::Input,
        Component::Type::Movement,
        Component::Type::Camera
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    CameraComponent* cameraComp = static_cast<CameraComponent*>(entity->components[Component::Type::Camera].get());
    cameraComp->camera = std::make_shared<Camera>();

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::camera() {
    std::vector<Component::Type> types = {
        Component::Type::Node,
        Component::Type::Transform,
        Component::Type::Movement, // TODO: take from to avatar
        Component::Type::Camera
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    auto cameraComponent = static_cast<CameraComponent*>(entity->components[Component::Type::Camera].get());
    cameraComponent->camera = std::make_shared<Camera>();

    auto movementComponent = static_cast<MovementComponent*>(entity->components[Component::Type::Movement].get());
    movementComponent->moveSpeed = 1.0;
    movementComponent->rotateSpeed = 0.1;

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::freeCamera() {
    std::vector<Component::Type> types = {
        Component::Type::Transform,
        Component::Type::Camera,
        Component::Type::Movement
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    auto cameraComponent = static_cast<CameraComponent*>(entity->components[Component::Type::Camera].get());
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}
