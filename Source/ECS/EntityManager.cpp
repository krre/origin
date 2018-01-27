#include "EntityManager.h"
#include "Systems/Systems.h"
#include "EntityBuilder.h"
#include "Components/Components.h"
#include <algorithm>

namespace Origin {

EntityManager::EntityManager() {
    initSystems();
    entityBuilder = std::make_unique<EntityBuilder>(this);
}

EntityManager::~EntityManager() {

}

void EntityManager::removeSystem(SystemType type) {
    updateSystems.erase(type);
    drawSystems.erase(type);
}

std::shared_ptr<System> EntityManager::getSystem(SystemType type) {
    auto it = updateSystems.find(type);
    if (it != updateSystems.end()) {
        return it->second;
    }
    std::shared_ptr<System> system = drawSystems.at(type);
    return system;
}

void EntityManager::addEntity(const std::shared_ptr<Entity>& entity) {
    entities[entity->getId()] = entity;
}

void EntityManager::removeEntity(const std::shared_ptr<Entity>& entity) {
//    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

std::shared_ptr<Entity> EntityManager::getEntity(EntityId id) {
    return entities[id];
}

void EntityManager::clearEntities() {
    entities.clear();
}

void EntityManager::initSystems() {
    // Order important!
    // This is also order of processing
    addUpdateSystem<MovementControllerSystem>();
    addUpdateSystem<CameraSystem>();
    addUpdateSystem<TransformSystem>();
    addUpdateSystem<NodeSystem>();
    addUpdateSystem<PhysicsSystem>();
    addUpdateSystem<OctreeSystem>();
    addDrawSystem<RenderSystem>();
}

Component* EntityManager::createComponent(Entity* entity, ComponentType type) {
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
    case ComponentType::Physics:
        entity->components[type] = std::make_shared<PhysicsComponent>();
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
    case ComponentType::Mesh: break;
    case ComponentType::Empty: break;
    }


    return entity->components[type].get();
}

std::shared_ptr<Entity> EntityManager::createComponents(const std::vector<ComponentType>& types) {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    for (const auto& type : types) {
        createComponent(entity.get(), type);
    }

    return entity;
}

void EntityManager::addComponent(Entity* entity, std::shared_ptr<Component> component) {
    entity->components[component->getType()] = component;
}

void EntityManager::removeComponent(Entity* entity, ComponentType type) {
    entity->components.erase(type);
}

void EntityManager::update(float dt) {
    for (const auto& system : updateSystems) {
        if (system.second->getActive()) {
            system.second->process(dt);
        }
    }
}

void EntityManager::draw() {
    for (const auto& system : drawSystems) {
        if (system.second->getActive()) {
            system.second->process(0); // dt is not used
        }
    }
}

} // Origin
