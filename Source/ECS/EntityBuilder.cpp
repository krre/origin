#include "EntityBuilder.h"
#include "Components/Components.h"
#include "../Graphics/Model.h"
#include "../Graphics/Mesh/Plane.h"


Entity* EntityBuilder::ground() {
    Entity* entity = new Entity;
    entity->addComponent<RenderComponent>();
    RenderComponent* renderComp = static_cast<RenderComponent*>(entity->getComponent(ComponentType::Render));
    Model* planeModel = new Model();
    planeModel->setMesh(new Plane);
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
