#include "Engine.h"
#include "../ECS/Systems/Systems.h"
#include "Components/Components.h"
#include <algorithm>

Engine::Engine() {
    initSystems();
}

void Engine::removeSystem(SystemType type) {
    systems.erase(type);
}

std::shared_ptr<System> Engine::getSystem(SystemType type) {
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

Component* Engine::createComponent(Entity* entity, ComponentType type) {
    switch (type) {
    case ComponentType::Camera:
        entity->components[type] = std::make_shared<CameraComponent>();
        break;
    case ComponentType::Light:
        entity->components[type] = std::make_shared<LightComponent>();
        break;
    case ComponentType::Material:
        entity->components[type] = std::make_shared<MaterialComponent>();
        break;
    case ComponentType::Mesh:
        entity->components[type] = std::make_shared<MeshComponent>();
        break;
    case ComponentType::Movement:
        entity->components[type] = std::make_shared<MovementComponent>();
        break;
    case ComponentType::Node:
        entity->components[type] = std::make_shared<NodeComponent>();
        break;
    case ComponentType::Render:
        entity->components[type] = std::make_shared<RenderComponent>();
        break;
    case ComponentType::Transform:
        entity->components[type] = std::make_shared<TransformComponent>();
        break;
    case ComponentType::MotionController:
        entity->components[type] = std::make_shared<MotionControllerComponent>();
        break;
    }

    return entity->components[type].get();
}

void Engine::createComponents(Entity *entity, std::vector<ComponentType> types) {
    for (auto type : types) {
        createComponent(entity, type);
    }
}

void Engine::addComponent(Entity* entity, std::shared_ptr<Component> component) {
    entity->components[component->getType()] = component;
}

void Engine::removeComponent(Entity* entity, ComponentType type) {
    entity->components.erase(type);
}
