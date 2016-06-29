#include "EntityBuilder.h"
#include "Components/Components.h"

Entity* EntityBuilder::ground() {
    Entity* entity = new Entity;
    entity->addComponent<NodeComponent>();
    entity->addComponent<RenderComponent>();
    entity->addComponent<TransformComponent>();

    return entity;
}

Entity* EntityBuilder::player() {
    Entity* entity = new Entity;
    entity->addComponent<NodeComponent>();
    entity->addComponent<TransformComponent>();
    entity->addComponent<InputComponent>();

    CameraComponent* cameraComponent = entity->addComponent<CameraComponent>();
    cameraComponent->camera = shared_ptr<Camera>(new Camera());

    return entity;
}
