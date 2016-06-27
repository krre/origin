#include "Engine.h"
#include "../ECS/Systems/InputSystem.h"
#include "../ECS/Systems/RenderSystem.h"
#include "../ECS/Systems/TransformSystem.h"

Engine::Engine() {

}

void Engine::addSystem(SystemType type) {
    switch (type) {
    case SystemType::Input:
        systems[type] = new InputSystem();
        break;
    case SystemType::Render:
        systems[type] = new RenderSystem();
        break;
    case SystemType::Transform:
        systems[type] = new TransformSystem();
        break;
    default:
        break;
    }
}

void Engine::removeSystem(SystemType type) {
    delete systems.at(type);
    systems.erase(type);
}

const System* Engine::getSystem(SystemType type) {
    return systems.at(type);
}

void Engine::clearSystems() {
    for (auto it: systems) {
        delete it.second;
    }
    systems.clear();
}

void Engine::addEntity(Entity* entity) {
    entities.push_back(entity);
}

void Engine::removeEntity(Entity* entity) {
    entities.remove(entity);
}

Entity* Engine::getEntity(EntityId id) {
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
    for (auto it: systems) {
        it.second->process(dt);
    }
}
