#include "Engine.h"
#include "../ECS/Systems/Systems.h"
#include "Components/Components.h"
#include <algorithm>

Engine::Engine() {
    initSystems();
}

void Engine::removeSystem(SystemType type) {
    updateSystems.erase(type);
    drawSystems.erase(type);
}

std::shared_ptr<System> Engine::getSystem(SystemType type) {
    auto it = updateSystems.find(type);
    if (it != updateSystems.end()) {
        return it->second;
    }
    std::shared_ptr<System> system = drawSystems.at(type);
    return system;
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

void Engine::initSystems() {
    // Order important!
    // This is also order of processing
    addUpdateSystem<MovementControllerSystem>();
    addUpdateSystem<CameraSystem>();
    addUpdateSystem<TransformSystem>();
    addUpdateSystem<NodeSystem>();
    addUpdateSystem<OctreeSystem>();
    addDrawSystem<RenderSystem>();
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
    case ComponentType::MovementController:
        entity->components[type] = std::make_shared<MovementControllerComponent>();
        break;
    case ComponentType::Octree:
        entity->components[type] = std::make_shared<OctreeComponent>();
        break;
    }

    return entity->components[type].get();
}

std::shared_ptr<Entity> Engine::createComponents(std::vector<ComponentType> types) {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    for (auto type : types) {
        createComponent(entity.get(), type);
    }

    return entity;
}

void Engine::addComponent(Entity* entity, std::shared_ptr<Component> component) {
    entity->components[component->getType()] = component;
}

void Engine::removeComponent(Entity* entity, ComponentType type) {
    entity->components.erase(type);
}

void Engine::update(float dt) {
    for (auto system : updateSystems) {
        if (system.second->getActive()) {
            system.second->process(dt);
        }
    }
}

void Engine::draw(float dt) {
    for (auto system : drawSystems) {
        if (system.second->getActive()) {
            system.second->process(dt);
        }
    }
}
