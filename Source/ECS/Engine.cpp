#include "Engine.h"
#include "../ECS/Systems/Systems.h"
#include "Components/Components.h"
#include <algorithm>

Engine::Engine() {
    initSystems();
}

void Engine::removeSystem(System::Type type) {
    systems.erase(type);
}

std::shared_ptr<System> Engine::getSystem(System::Type type) {
    return systems.at(type);
}

void Engine::clearSystems() {
    systems.clear();
}

void Engine::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}

void Engine::removeEntity(std::shared_ptr<Entity> entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

std::shared_ptr<Entity> Engine::getEntity(EntityId id) {
    for (auto it: entities) {
        if (it->getId() == id) {
            return it;
        }
    }

    return nullptr;
}

void Engine::clearEntities() {
    entities.clear();
}

void Engine::process(float dt) {
    for (auto system : systems) {
        if (system.second->getActive()) {
            system.second->process(dt);
        }
    }
}

void Engine::initSystems() {
    // Order important!
    // This is also order of processing
    addSystem<MotionControllerSystem>();
    addSystem<CameraSystem>();
    addSystem<TransformSystem>();
    addSystem<NodeSystem>();
    addSystem<RenderSystem>();
}

Component* Engine::createComponent(Entity* entity, Component::Type type) {
    switch (type) {
    case Component::Type::Camera:
        entity->components[type] = std::make_shared<CameraComponent>();
        break;
    case Component::Type::Light:
        entity->components[type] = std::make_shared<LightComponent>();
        break;
    case Component::Type::Material:
        entity->components[type] = std::make_shared<MaterialComponent>();
        break;
    case Component::Type::Mesh:
        entity->components[type] = std::make_shared<MeshComponent>();
        break;
    case Component::Type::Movement:
        entity->components[type] = std::make_shared<MovementComponent>();
        break;
    case Component::Type::Node:
        entity->components[type] = std::make_shared<NodeComponent>();
        break;
    case Component::Type::Render:
        entity->components[type] = std::make_shared<RenderComponent>();
        break;
    case Component::Type::Transform:
        entity->components[type] = std::make_shared<TransformComponent>();
        break;
    case Component::Type::MotionController:
        entity->components[type] = std::make_shared<MotionControllerComponent>();
        break;
    }

    return entity->components[type].get();
}

void Engine::createComponents(Entity *entity, std::vector<Component::Type> types) {
    for (auto type : types) {
        createComponent(entity, type);
    }
}

void Engine::addComponent(Entity* entity, std::shared_ptr<Component> component) {
    entity->components[component->getType()] = component;
}

void Engine::removeComponent(Entity* entity, Component::Type type) {
    entity->components.erase(type);
}
