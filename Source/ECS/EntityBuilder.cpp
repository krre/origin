#include "EntityBuilder.h"
#include "Engine.h"
#include "Components/Components.h"
#include "../Graphics/Model.h"
#include "../Graphics/Mesh/Plane.h"
#include "../Graphics/Material.h"

std::shared_ptr<Entity> EntityBuilder::ground() {
    std::vector<Component::Type> types = {
        Component::Type::Render,
        Component::Type::Transform,
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    auto planeModel = std::make_shared<Model>();

    auto planeMesh = std::make_shared<Plane>(1, 1);
    planeModel->setMesh(planeMesh);

    auto planeMaterial = std::make_shared<Material>();
    planeMaterial->setColor(Color(0, 0, 1, 1));
    planeModel->setMaterial(planeMaterial);

    RenderComponent* renderComp = static_cast<RenderComponent*>(entity->components[Component::Type::Render].get());
    renderComp->drawable = planeModel;

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

    auto cameraComponent = static_cast<CameraComponent*>(entity->components[Component::Type::Camera].get());
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}

std::shared_ptr<Entity> EntityBuilder::camera() {
    std::vector<Component::Type> types = {
        Component::Type::Node,
        Component::Type::Transform,
        Component::Type::Camera
    };
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    Engine::getInstance()->createComponents(entity.get(), types);

    auto cameraComponent = static_cast<CameraComponent*>(entity->components[Component::Type::Camera].get());
    cameraComponent->camera = std::make_shared<Camera>();

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
