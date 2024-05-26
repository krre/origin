#include "EntityManager.h"
#include "Graphics/Render/SceneRenderer.h"
#include "Systems/Systems.h"
#include "EntityBuilder.h"
#include "Components/Components.h"
#include <algorithm>

EntityManager::EntityManager(Object* parent) : SingleObject(parent) {
    initSystems();
    entityBuilder = std::make_unique<EntityBuilder>(this);
}

EntityManager::~EntityManager() {

}

void EntityManager::removeSystem(System::Type type) {
    systems.erase(type);
}

std::shared_ptr<System> EntityManager::getSystem(System::Type type) {
    auto it = systems.find(type);
    if (it != systems.end()) {
        return it->second;
    }
    return nullptr;
}

void EntityManager::addEntity(const std::shared_ptr<Entity>& entity) {
    entities[entity->getId()] = entity;
}

void EntityManager::removeEntity(const std::shared_ptr<Entity>& entity) {
//    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

std::shared_ptr<Entity> EntityManager::getEntity(Core::EntityId id) {
    return entities[id];
}

void EntityManager::clearEntities() {
    entities.clear();
}

void EntityManager::initSystems() {
    // Order important!
    // This is also order of processing
    addSystem<MovementControllerSystem>();
    addSystem<CameraSystem>();
    addSystem<TransformSystem>();
    addSystem<PhysicsSystem>();
    addSystem<OctreeSystem>();
}

Component* EntityManager::createComponent(Entity* entity, Component::Type type) {
    switch (type) {
        case Component::Type::Camera:
            entity->addComponent(std::make_shared<CameraComponent>());
            break;
        case Component::Type::Light:
            entity->addComponent(std::make_shared<LightComponent>());
            break;
        case Component::Type::Material:
            entity->addComponent(std::make_shared<MaterialComponent>());
            break;
        case Component::Type::Movement:
            entity->addComponent(std::make_shared<MovementComponent>());
            break;
        case Component::Type::Render:
            entity->addComponent(std::make_shared<RenderComponent>());
            break;
        case Component::Type::Physics:
            entity->addComponent(std::make_shared<PhysicsComponent>());
            break;
        case Component::Type::Transform:
            entity->addComponent(std::make_shared<TransformComponent>());
            break;
        case Component::Type::MovementController:
            entity->addComponent(std::make_shared<MovementControllerComponent>());
            break;
        case Component::Type::Octree:
            entity->addComponent(std::make_shared<OctreeComponent>());
            break;
        case Component::Type::Mesh: break;
        case Component::Type::Empty: break;
    }

    return entity->getComponent(type);
}

std::shared_ptr<Entity> EntityManager::createComponents(const std::vector<Component::Type>& types) {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    for (const auto& type : types) {
        createComponent(entity.get(), type);
    }

    return entity;
}

void EntityManager::addComponent(Entity* entity, std::shared_ptr<Component> component) {
    entity->addComponent(component);
}

void EntityManager::removeComponent(Entity* entity, Component::Type type) {
    entity->removeComponent(type);
}

void EntityManager::update(Scene* scene, float dt) {
    for (const auto& system : systems) {
        if (system.second->getActive()) {
            system.second->process(dt);
        }
    }
}
