#include "EntityBuilder.h"
#include "Components/Components.h"
#include "../Graphics/Model.h"
#include "../Graphics/Mesh/Plane.h"
#include "../Graphics/Material.h"


std::shared_ptr<Entity> EntityBuilder::ground() {
    auto entity = std::make_shared<Entity>();
    RenderComponent* renderComp = static_cast<RenderComponent*>(entity->createComponent(Component::Type::Render));
    auto planeModel = std::make_shared<Model>();

    auto planeMesh = std::make_shared<Plane>(1, 1);
    planeModel->setMesh(planeMesh);

    auto planeMaterial = std::make_shared<Material>();
    planeMaterial->setColor(Color(0, 0, 1, 1));
    planeModel->setMaterial(planeMaterial);

    renderComp->drawable = planeModel;
    entity->createComponent(Component::Type::Transform);

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::avatar() {
    auto entity = std::make_shared<Entity>();
    entity->createComponent(Component::Type::Node);
    entity->createComponent(Component::Type::Transform);
    entity->createComponent(Component::Type::Input);
    entity->createComponent(Component::Type::Movement);

    auto cameraComponent = static_cast<CameraComponent*>(entity->createComponent(Component::Type::Camera));
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::camera() {
    auto entity = std::make_shared<Entity>();
    entity->createComponent(Component::Type::Node);
    entity->createComponent(Component::Type::Transform);

    auto cameraComponent = static_cast<CameraComponent*>(entity->createComponent(Component::Type::Camera));
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::freeCamera() {
    auto entity = std::make_shared<Entity>();
    entity->createComponent(Component::Type::Transform);
    entity->createComponent(Component::Type::Movement);

    auto cameraComponent = static_cast<CameraComponent*>(entity->createComponent(Component::Type::Camera));
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}
