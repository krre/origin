#include "EntityBuilder.h"
#include "Components/Components.h"
#include "../Graphics/Model.h"
#include "../Graphics/Mesh/Plane.h"
#include "../Graphics/Material.h"


Entity* EntityBuilder::ground() {
    Entity* entity = new Entity;
    entity->addComponent<RenderComponent>();
    RenderComponent* renderComp = static_cast<RenderComponent*>(entity->getComponent(ComponentType::Render));
    std::shared_ptr<Model> planeModel = std::make_shared<Model>();

    std::shared_ptr<Plane> planeMesh = std::make_shared<Plane>(1, 1);
    planeModel->setMesh(planeMesh);

    std::shared_ptr<Material> planeMaterial = std::make_shared<Material>();
    planeMaterial->setColor(Color(0, 0, 1, 1));
    planeModel->setMaterial(planeMaterial);

    renderComp->drawable = planeModel;
    entity->addComponent<TransformComponent>();

    return entity;
}

Entity* EntityBuilder::avatar() {
    Entity* entity = new Entity;
    entity->addComponent<NodeComponent>();
    entity->addComponent<TransformComponent>();
    entity->addComponent<InputComponent>();
    entity->addComponent<MovementComponent>();

    CameraComponent* cameraComponent = entity->addComponent<CameraComponent>();
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}

Entity* EntityBuilder::camera() {
    Entity* entity = new Entity;
    entity->addComponent<NodeComponent>();
    entity->addComponent<TransformComponent>();

    CameraComponent* cameraComponent = entity->addComponent<CameraComponent>();
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}

Entity* EntityBuilder::freeCamera() {
    Entity* entity = new Entity;
    entity->addComponent<TransformComponent>();
    entity->addComponent<MovementComponent>();

    CameraComponent* cameraComponent = entity->addComponent<CameraComponent>();
    cameraComponent->camera = std::make_shared<Camera>();

    return entity;
}
